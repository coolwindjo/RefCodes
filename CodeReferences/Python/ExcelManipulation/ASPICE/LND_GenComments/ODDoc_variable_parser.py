import re
from collections import namedtuple
import ODDoc_util as util

def parse_variable(header_file):
    var_list = []

    VarInfo = namedtuple('VarInfo', 'type name accessability desc unit range')

    try:
        f = open(header_file, "r")
        header_code = f.read()
        f.close()
    except IOError:
        header_code = ""

    # class ClassName { }
    pat_class = r'class \w+\s+{.+}'
    found = re.search(pat_class, header_code, re.DOTALL)

    if found is None:
        # class ClassName : public Parent {}
        pat_class = r'class \w+\s{0,10}?[:]\s{0,10}?\w+\s{0,10}?\w+\s+{.+}'
        found = re.search(pat_class, header_code, re.DOTALL)

    if found is not None:

        idx_start = found.start()
        idx_end = found.end()

        class_code = header_code[idx_start:idx_end-1]
        print(class_code)

        # remove definitions of structures or enumerations in the class.
        pat_struct = r'struct\s+\w+\s+{.+}'
        class_code = re.sub(pat_struct, '', class_code, 0, re.DOTALL)

        pat_struct = r'enum\s+\w+\s+{.+}'
        class_code = re.sub(pat_struct, '', class_code, 0, re.DOTALL)

        print(class_code)

        s_public = re.search(r'public:', class_code)
        public_begin = 0
        if s_public is not None:
            public_begin = s_public.end()

        s_protected = re.search(r'protected:', class_code)
        protected_begin = 0
        if s_protected is not None:
            protected_begin = s_protected.end()

        s_private = re.search(r'private:', class_code)
        private_begin = 0
        if s_private is not None:
            private_begin = s_private.end()


        # constant pattern
        var_pattern = r'const\s+(?P<type>\w+\s{0,1}[*]{0,1})\s+(?P<name>\w+)\s+[=]\s+(?P<value>.+?)[;]\s+/[*][*]<(?P<comment>.+?)[*]/'
        for f in re.finditer(var_pattern, class_code, re.DOTALL):
            var_info = parse_line(f, class_code, public_begin, protected_begin, private_begin)
            var = VarInfo(type=var_info[0], name=var_info[1], desc=var_info[2], accessability=var_info[3],
                          unit=var_info[4], range=var_info[5])
            if var.type != "const" and var.type != "static":
                var_list.append(var)

        var_pattern = r"\s+(?P<type>\w+\s{0,1}[*]{0,1})\s+(?P<name>.+?);\s+/[*][*]<(?P<comment>.+?)[*]/"
        for f in re.finditer(var_pattern, class_code):
            var_info = parse_line(f, class_code, public_begin, protected_begin, private_begin)
            var = VarInfo(type=var_info[0], name=var_info[1], desc=var_info[2], accessability=var_info[3], unit=var_info[4], range=var_info[5])
            if var.type != "const" and var.type != "static":
                var_list.append(var)


    return var_list

def parse_line(f, class_code, public_begin, protected_begin, private_begin):

    var_values = f.groupdict()
    var_type = var_values['type']
    var_name = var_values['name']
    var_comment = var_values['comment']

    var_name = re.sub(r"[[].+[]]", "", var_name)

    unit_pattern = r"\sunit:(?P<unit>[a-zA-Z0-9_/]+)"
    unit_found = re.search(unit_pattern, var_comment)
    if (unit_found is not None):
        unit = unit_found.groupdict()['unit']
        var_comment = re.sub(unit_pattern, "", var_comment)
        # print(unit)
    else:
        unit = "n/a"

    var_comment = util.remove_proceeding_space(var_comment)

    range_pattern = r"\srange:(?P<range>[()a-zA-Z0-9_/~.+-]+)"
    range_found = re.search(range_pattern, var_comment)
    if (range_found is not None):
        var_range = range_found.groupdict()['range']
        var_comment = re.sub(range_pattern, "", var_comment)
        # print(range)
    else:
        var_range = "n/a"

    # test for accessibility
    access = ""

    var_type_converted = var_type.replace(r'*', r'[*]')
    s_var = re.search(var_type_converted + '\s+' + var_name + '.{0,100};', class_code)
    if s_var is not None:
        func_begin = s_var.start()

        diff_pub = func_begin - public_begin
        if diff_pub < 0:
            diff_pub = 100000000
        diff_pro = func_begin - protected_begin
        if diff_pro < 0:
            diff_pro = 100000000
        diff_pri = func_begin - private_begin
        if diff_pri < 0:
            diff_pri = 100000000

        if diff_pub >= 0 and diff_pub < diff_pro and diff_pub < diff_pri:
            access = "public"
        elif diff_pri >= 0 and diff_pri < diff_pro and diff_pri < diff_pub:
            access = "private"
        elif diff_pro >= 0 and diff_pro < diff_pri and diff_pro < diff_pub:
            access = "private"
        else:
            access = "not defined"

    var = []
    var.append(var_type)
    var.append(var_name)
    var.append(var_comment)
    var.append(access)
    var.append(unit)
    var.append(var_range)

    return var
