import re
s1 = 'apple  kiwi  banna'
s2= '서울갂 은평구'
try:
    match = re.search('ki\di', s1 ) #[0-9]
    if (match != None): print( match.group() )
    match = re.search('ki\Di', s1 ) #[^0-9]
    if (match != None): print( match.group() ) 
    match = re.search('ki\s+i', s1 ) #[ \n\t\r]
    if (match != None): print( match.group() ) 
    match = re.search('ki\Si', s1 ) #[^ \n\t\r]
    if (match != None): print( match.group() ) 
    match = re.search('\S+\s+\S+', s1 ) #[^ \n\t\r]
    if (match != None): print( match.group() ) 
    match = re.search('ki\wi', s1 )#[a-zA-Z0-9가-힣_]
    if (match != None): print( match.group() ) 
    match = re.search('ki\Wi', s1 )#[^a-zA-Z0-9가-힣_]
    if (match != None): print( match.group() ) 
    match = re.search('ki[\w.#]i', s1 )#[^a-zA-Z0-9가-힣_]
    if (match != None): print( match.group() ) 
except Exception as err:
    print('not found')

