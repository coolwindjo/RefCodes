"""
Object detection documentation.
"""

import re
import xlsxwriter as xw
import ODDoc_util as util
import ODDoc_func_parser as fparser
import ODDoc_variable_parser as vparser

header_file_name = "D:/GitRepository/Fmain/src/component/lane/lmd/LND_BottsDotsDetector_data.h"
#header_file_name = "examples/CODEdgeProcessor.h"

try:
    f = open(header_file_name, "r")
    code = f.read()
    f.close()
except IOError:
    code = ""

workbook = xw.Workbook(header_file_name[:-2] + ".xlsx")
head_format = workbook.add_format()
head_format.set_bg_color("#C0C0C0")
head_format.set_bold()
head_format.set_left()
head_format.set_right()
head_format.set_top()
head_format.set_bottom()

merge_format = workbook.add_format({'align':'left',
                                    'valign':'top'})
merge_format.set_left()
merge_format.set_right()
merge_format.set_top()
#merge_format.set_bottom()

struct_head_format = workbook.add_format()
struct_head_format.set_bg_color("#C0C0C0")
struct_head_format.set_left()
struct_head_format.set_right()
struct_head_format.set_top()
struct_head_format.set_bottom()

cell_format = workbook.add_format()
cell_format.set_left()
cell_format.set_right()
cell_format.set_align('top')

cell_top_format = workbook.add_format()
cell_top_format.set_left()
cell_top_format.set_right()
cell_top_format.set_top()

cell_bottom_format = workbook.add_format()
cell_bottom_format.set_left()
cell_bottom_format.set_right()
cell_bottom_format.set_bottom()

"""
Search for struct
"""
pattern = r"/[*][*]\s+" \
          r"\s+[*]{0,1}\s{0,1}(?P<struct_desc>.+)\s+" \
          r"[*]/\s+" \
          r"typedef\s+struct\s*.*\s*{"

worksheet = workbook.add_worksheet("struct")

worksheet.write('A1', "Name", head_format)
worksheet.write('B1', "Type", head_format)
worksheet.write('C1', "Description", head_format)
worksheet.write('D1', "Unit", head_format)
worksheet.write('E1', "Range", head_format)

num_line = 2
for m in re.finditer(pattern, code):
    values = m.groupdict()

    # find }
    field_begin = m.end()
    field_end = code.find("}", field_begin)
    struct_name_field_end = code.find(";", field_end)

    # find struct name
    struct_name_pattern = r"\s*(?P<struct_name>\w+)"
    struct_name_field = code[field_end+1:struct_name_field_end]
    struct_name_found = re.search(struct_name_pattern, struct_name_field)
    if(struct_name_found is not None):
        struct_name = struct_name_found.groupdict()

        worksheet.write('A' + str(num_line), struct_name['struct_name'], struct_head_format)
        worksheet.write('B' + str(num_line), "struct", struct_head_format)
        worksheet.write('C' + str(num_line), values['struct_desc'], struct_head_format)
        worksheet.write('D' + str(num_line), "", struct_head_format)
        worksheet.write('E' + str(num_line), "", struct_head_format)

        num_line = num_line + 1

        if field_end != -1:
            code_field = code[field_begin:field_end]
            #print(code_field)
            field_pattern = r"\s+(?P<type>\w+\s{0,1}[*]{0,1})\s+(?P<name>.+?);\s+/[*][*]<(?P<comment>.+?)[*]/"
            for f in re.finditer(field_pattern, code_field, re.DOTALL):
                field_values = f.groupdict()
                #print(field_values['type'])
                #print(field_values['name'])
                print(field_values['comment'])

                field_name = field_values['name']
                field_name = re.sub(r"[[].+[]]", "", field_name)

                comment = field_values['comment']
                unit_pattern = r"\sunit:(?P<unit>[a-zA-Z0-9_/]+)"
                unit_found = re.search(unit_pattern, comment)
                if(unit_found is not None):
                    unit = unit_found.groupdict()['unit']
                    comment = re.sub(unit_pattern, "", comment)
                    #print(unit)
                else:
                    unit = "n/a"

                comment = util.remove_proceeding_space(comment)

                range_pattern = r"\srange:(?P<range>[()a-zA-Z0-9_/~.+-]+)"
                range_found = re.search(range_pattern, comment)
                if (range_found is not None):
                    val_range = range_found.groupdict()['range']
                    comment = re.sub(range_pattern, "", comment)
                    #print(range)
                else:
                    val_range = "n/a"

                worksheet.write('A' + str(num_line), field_name, cell_format)
                worksheet.write('B' + str(num_line), field_values['type'], cell_format)
                worksheet.write('C' + str(num_line), comment, cell_format)
                worksheet.write('D' + str(num_line), unit, cell_format)
                worksheet.write('E' + str(num_line), val_range, cell_format)

                num_line = num_line + 1
            


"""
Search for enum
"""
worksheet = workbook.add_worksheet("enum")

worksheet.write('A1', "Name", head_format)
worksheet.write('B1', "Description", head_format)

pattern = r"/[*][*]\s+" \
          r"\s+[*]{0,1}\s{0,1}(?P<enum_desc>.+)\s+" \
          r"[*]/\s+" \
          r"enum\s+(?P<enum_name>\w+)\s+{"

num_line = 2
for m in re.finditer(pattern, code):
    values = m.groupdict()
    print("enum: " + values['enum_name'])
    print("Description: " + values['enum_desc'])

    worksheet.write('A' + str(num_line), values['enum_name'], struct_head_format)
    worksheet.write('B' + str(num_line), values['enum_desc'], struct_head_format)

    num_line = num_line + 1

    # find }
    field_begin = m.end()
    field_end = code.find("}", field_begin)
    if field_end != -1:
        code_field = code[field_begin:field_end]
        #print(code_field)
        field_pattern = r"\s+(?P<enum_item>\w+)[,=0-9\s]+/[*][*]<(?P<comment>.+?)[*]/"
        for f in re.finditer(field_pattern, code_field, re.DOTALL):
            field_values = f.groupdict()
            print(field_values['enum_item'])
            print(field_values['comment'])

            enum_item = field_values['enum_item']
            comment = field_values['comment']
            comment = util.remove_proceeding_space(comment)

            worksheet.write('A' + str(num_line), enum_item, cell_format)
            #worksheet.write('B' + str(num_line), field_values['type'], cell_format)
            worksheet.write('B' + str(num_line), comment, cell_format)

            num_line = num_line + 1

"""
Search for function
"""
worksheet = workbook.add_worksheet("function")
func_list = fparser.parse_function(header_file_name)

worksheet.write('A1', "Method Name", head_format)
worksheet.write('B1', "Accessibility", head_format)
worksheet.write('C1', "Description", head_format)
worksheet.write('D1', "Inputs/Outputs", head_format)

num_functions = len(func_list)
num_line = 1
for idx in range(0, num_functions):
    num_line = num_line + 1
    start_line = num_line
    if func_list[idx].return_type != "":
        func_def = func_list[idx].return_type + " " + func_list[idx].name + "()"
    else:
        func_def = func_list[idx].name + "()"

    # The following information is updated when the cells are merged.
    worksheet.write('A' + str(num_line), func_def, cell_format)

    func_accessibility = func_list[idx].accessibility
    worksheet.write('B' + str(num_line), func_accessibility, cell_format)

    func_desc = func_list[idx].desc
    worksheet.write('C' + str(num_line), func_desc, cell_format)

    arg_list = func_list[idx].arg_list
    # Input arguments
    num_input = 0
    col_arg = 'D'
    for idx_arg in range(0, len(arg_list)):
        if arg_list[idx_arg].inout == 'in':
            num_input = num_input + 1
            if num_input > 1:
                num_line = num_line + 1
            arg_desc = '*Input ' + str(num_input)

            if num_input == 1:
                worksheet.write(col_arg + str(num_line), arg_desc, cell_top_format)
            else:
                worksheet.write(col_arg + str(num_line), arg_desc, cell_format)

            arg_desc = ' -name: ' + arg_list[idx_arg].name
            num_line = num_line + 1
            worksheet.write(col_arg + str(num_line), arg_desc, cell_format)

            arg_desc = ' -type: ' + arg_list[idx_arg].type
            num_line = num_line + 1
            worksheet.write(col_arg + str(num_line), arg_desc, cell_format)

            arg_desc = ' -desc: ' + arg_list[idx_arg].desc
            num_line = num_line + 1
            worksheet.write(col_arg + str(num_line), arg_desc, cell_format)

            arg_desc = ' -unit: ' + arg_list[idx_arg].unit
            num_line = num_line + 1
            worksheet.write(col_arg + str(num_line), arg_desc, cell_format)

            arg_desc = ' -range: ' + arg_list[idx_arg].range
            num_line = num_line + 1
            worksheet.write(col_arg + str(num_line), arg_desc, cell_format)
    if num_input == 0:
        worksheet.write(col_arg + str(num_line), "*Input: n/a", cell_top_format)

    num_output = 0
    for idx_arg in range(0, len(arg_list)):
        if arg_list[idx_arg].inout == 'out':
            num_output = num_output + 1;
            arg_desc = '*Output ' + str(num_output)
            num_line = num_line + 1
            worksheet.write(col_arg + str(num_line), arg_desc, cell_format)

            arg_desc = ' -name: ' + arg_list[idx_arg].name
            num_line = num_line + 1
            worksheet.write(col_arg + str(num_line), arg_desc, cell_format)

            arg_desc = ' -type: ' + arg_list[idx_arg].type
            num_line = num_line + 1
            worksheet.write(col_arg + str(num_line), arg_desc, cell_format)

            arg_desc = ' -desc: ' + arg_list[idx_arg].desc
            num_line = num_line + 1
            worksheet.write(col_arg + str(num_line), arg_desc, cell_format)

            arg_desc = ' -unit: ' + arg_list[idx_arg].unit
            num_line = num_line + 1
            worksheet.write(col_arg + str(num_line), arg_desc, cell_format)

            arg_desc = ' -range: ' + arg_list[idx_arg].range
            num_line = num_line + 1
            worksheet.write(col_arg + str(num_line), arg_desc, cell_format)

    if func_list[idx].return_desc != "":
        num_output = num_output + 1;
        arg_desc = '*Output ' + str(num_output)
        num_line = num_line + 1
        worksheet.write(col_arg + str(num_line), arg_desc, cell_format)

        arg_desc = ' -return value'
        num_line = num_line + 1
        worksheet.write(col_arg + str(num_line), arg_desc, cell_format)

        arg_desc = ' -type: ' + func_list[idx].return_type
        num_line = num_line + 1
        worksheet.write(col_arg + str(num_line), arg_desc, cell_format)

        arg_desc = ' -desc: ' + func_list[idx].return_desc
        num_line = num_line + 1
        worksheet.write(col_arg + str(num_line), arg_desc, cell_format)

        arg_desc = ' -unit: ' + func_list[idx].return_unit
        num_line = num_line + 1
        worksheet.write(col_arg + str(num_line), arg_desc, cell_format)

        arg_desc = ' -range: ' + func_list[idx].return_range
        num_line = num_line + 1
        worksheet.write(col_arg + str(num_line), arg_desc, cell_format)

    if num_output == 0:
        num_line = num_line + 1
        worksheet.write(col_arg + str(num_line), "*Output: n/a", cell_format)

    end_line = num_line
    worksheet.merge_range(start_line-1, 0, end_line-1, 0, func_def, merge_format)
    worksheet.merge_range(start_line - 1, 1, end_line - 1, 1, func_accessibility, merge_format)
    worksheet.merge_range(start_line - 1, 2, end_line - 1, 2, func_desc, merge_format)

"""
Search for member variables
"""
worksheet = workbook.add_worksheet("variable")
var_list = vparser.parse_variable(header_file_name)

print(var_list)

worksheet.write('A1', "Name", head_format)
worksheet.write('B1', "Type", head_format)
worksheet.write('C1', "Accessibility", head_format)
worksheet.write('D1', "Description", head_format)
worksheet.write('E1', "Unit", head_format)
worksheet.write('F1', "Range", head_format)

num_variables = len(var_list)
num_line = 1
for idx in range(0, num_variables):
    num_line = num_line + 1
    start_line = num_line

    worksheet.write('A' + str(num_line), var_list[idx].name, cell_format)
    worksheet.write('B' + str(num_line), var_list[idx].type, cell_format)
    worksheet.write('C' + str(num_line), var_list[idx].accessability, cell_format)
    worksheet.write('D' + str(num_line), var_list[idx].desc, cell_format)
    worksheet.write('E' + str(num_line), var_list[idx].unit, cell_format)
    worksheet.write('F' + str(num_line), var_list[idx].range, cell_format)

    arg_list = func_list[idx].arg_list

workbook.close()

