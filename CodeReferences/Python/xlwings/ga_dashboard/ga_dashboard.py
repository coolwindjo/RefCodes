# Follow the blog post here: http://blog.zoomeranalytics.com/google-analytics/

import os
import numpy as np
import pandas as pd
from google2pandas import GoogleAnalyticsQueryV4
from datetime import datetime
import xlwings as xw

# Client Secrets file: same dir as this file
client_secrets = os.path.abspath(os.path.join(os.path.dirname(__file__),
                                              'client_secrets_v4.json'))


def behavior(start_date, end_date, account_name, property_name, profile_name, max_results):
    # Let pandas fetch the data from Google Analytics, returns a generator object
    query = {
        'reportRequests': [{

            'account_name' : account_name,

            'property_name' : property_name,

            'profile_name' : profile_name,

            'index_col' : 0,
            
            'dateRanges': [{
                'startDate' : start_date,
                'endDate'   : end_date }],
                
            'parse_dates' : {'datetime' : ['date', 'hour', 'minute']},
            'date_parser' : lambda x: datetime.strptime(x, '%Y%m%d %H %M'),
            'max_results' : max_results,
            'chunksize' : 10000,
            'dimensions' : [
                {'name' : 'ga:date'}, 
                {'name' : 'ga:hour'},
                {'name' : 'ga:minute'}],
                
            'metrics'   : [
                {'expression' : 'ga:pageviews'}],
                
        }]
    }
    conn = GoogleAnalyticsQueryV4(secrets=client_secrets)
    df_chunks = conn.execute_query(query)

    # Concatenate the chunks into a DataFrame and get number of rows
    df = pd.concat(df_chunks)
    num_rows = df.shape[0]

    # Resample into half-hour buckets
    df = df.resample('30Min', how='sum')

    # Create the behavior table (half-hour x weekday)
    grouped = df.groupby([df.index.time, df.index.weekday])
    behavior = grouped['pageviews'].aggregate(np.sum).unstack()

    # Make sure the table covers all hours and weekdays
    behavior = behavior.reindex(index=pd.date_range("00:00", "23:30", freq="30min").time,
                                columns=range(7))
    behavior.columns = ['MO', 'TU', 'WE', 'TH', 'FR', 'SA', 'SU']

    return behavior, num_rows


def refresh():
    """
    Refreshes the tables in Excel given the input parameters.
    """
    # Connect to the Workbook
    sht = xw.Book.caller().sheets['Sheet1']

    # Read input
    start_date = sht.range('start_date').value
    end_date = sht.range('end_date').value
    account_name = sht.range('account').value
    property_name = sht.range('property').value
    profile_name = sht.range('view').value
    max_results = sht.range('max_rows').value

    # Clear Content
    sht.range('behavior').clear_contents()
    sht.range('effective').clear_contents()

    # Behavior table
    df_behavior, num_rows = behavior(start_date, end_date, account_name, property_name, profile_name, max_results)

    # Write to Excel.
    # Time-only values are currently a bit of a pain on Windows, so we set index=False.
    sht.range('behavior').options(index=False).value = df_behavior
    sht.range('effective').value = num_rows

if __name__ == '__main__':
    # To run from Python. Not needed when called from Excel.
    path = os.path.abspath(os.path.join(os.path.dirname(__file__), 'ga_dashboard.xlsm'))
    xw.Book.set_mock_caller(path)
    refresh()
