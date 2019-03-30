import re
from collections import namedtuple
import ODDoc_util as util

def parse_function(header_file):
    func_list = []

    try:
        f = open(header_file, "r")
        header_code = f.read()
        f.close()
    except IOError:
        header_code = ""

    pattern = r"/[*][*]\s+" \
              r"[*]{0,1}\s?@fn\s+(?P<func_def>[~]{0,1}.+)"

    for m in re.finditer(pattern, header_code):
        values = m.groupdict()
        idx_start = m.end()
        idx_end = header_code.find(r"*/", idx_start)

       # print(m)
        func_def = values['func_def']
        # parse function definition.
        # function pattern: [qualifier] [return type] [function name]()
        print("func definition")
        print(func_def)

        # test for inline.
        pat_qualifier = r'inline\s'
        f = re.search(pat_qualifier, func_def)
        if f is not None:
            inline_function = True
            func_def = re.sub(pat_qualifier, '', func_def)
            print(func_def)
        else:
            inline_function = False

        # test for static
        pat_qualifier = r'static\s'
        f = re.search(pat_qualifier, func_def)
        if f is not None:
            static_function = True
            func_def = re.sub(pat_qualifier, '', func_def)
            print(func_def)
        else:
            static_function = False

        # get remaining information.
        arg_def = ""
        func_name = ""
        return_type = ""
        pat_func = r'(?P<return_type>.+?)\s+(?P<func_name>\w+)\s{0,100}[(]'
        f = re.search(pat_func, func_def)
        if f is not None:
            func_values = f.groupdict()

            return_type = func_values['return_type']
            func_name = func_values['func_name']
            print(return_type)
            print(func_name)
        else:
            # constructor / destructor
            pat_func = r'(?P<func_name>[~]{0,1}\w+)[(]'
            f = re.search(pat_func, func_def)
            if f is not None:
                func_values = f.groupdict()

                return_type = ""
                func_name = func_values['func_name']
                print(return_type)
                print(func_name)

        arg_list = [];
        if f is not None:
            arg_def = func_def[f.end():]
            #print(arg_list)

            pat_arg = r'(?P<type>.+?)\s[(]?[&]?(?P<name>\w+)[,)[]{1,2}(?P<array_size>\w*)[]]?'
            ArgInfo = namedtuple('ArgInfo', 'type name desc inout unit range')
            for a in re.finditer(pat_arg, arg_def):
                if a is not None:
                    arg_values = a.groupdict()
                    arg_type = arg_values['type']
                    arg_name = arg_values['name']
                    arg_array_size = arg_values['array_size']

                    arg_type = util.remove_proceeding_space(arg_type)
                    arg_name = util.remove_proceeding_space(arg_name)
                    if arg_array_size != "":
                        arg_array_size = util.remove_proceeding_space(arg_array_size)
                        print(arg_array_size)
                        arg_type = arg_type + ' &[' + arg_array_size + ']'

                    print(arg_type)
                    print(arg_name)

                    arg = ArgInfo(type=arg_type, name=arg_name, desc="", inout="", unit="", range="")
                    arg_list.append(arg)

        func_info = header_code[idx_start:idx_end]
        pat_desc = r'@brief\s+(?P<func_desc>.+)'
        d = re.search(pat_desc, func_info)
        if d is not None:
            func_desc = d.groupdict()['func_desc']
        else:
            func_desc = ""

        pat_arg_desc = r'@param\s+(?P<name>\w+)\s*(?P<desc>.*)'
        for a in re.finditer(pat_arg_desc, func_info):
            if a is not None:
                arg_values = a.groupdict()
                arg_name = arg_values['name']
                arg_desc = arg_values['desc']

                pat_inout = r'[:]\s{0,100}?[[](?P<inout>\w+)[]]\s{0,100}?(?P<desc>.+)'
                inout = re.search(pat_inout, arg_desc)
                if inout is not None:
                    desc_values = inout.groupdict()
                    arg_inout = desc_values['inout']
                    arg_desc = desc_values['desc']
                else:
                    arg_inout = ''

                for i in range(0, len(arg_list)):
                    if arg_name == arg_list[i].name:
                        ret = util.get_range(arg_desc)
                        arg_desc = ret[0]
                        arg_range = ret[1]

                        ret = util.get_unit(arg_desc)
                        arg_desc = ret[0]
                        arg_unit = ret[1]

                        arg_list[i] = arg_list[i]._replace(desc = arg_desc)
                        arg_list[i] = arg_list[i]._replace(inout=arg_inout)
                        arg_list[i] = arg_list[i]._replace(range=arg_range)
                        arg_list[i] = arg_list[i]._replace(unit=arg_unit)

        pat_return = r'@return\s+(?P<return_desc>.+)'
        ret = re.search(pat_return, func_info)
        if ret is not None:
            ret_values = ret.groupdict()
            return_desc = ret_values['return_desc']

            ret = util.get_range(return_desc)
            return_desc = ret[0]
            return_range = ret[1]

            ret = util.get_unit(return_desc)
            return_desc = ret[0]
            return_unit = ret[1]
        else:
            return_desc = ""
            return_range = ""
            return_unit = ""

        print(func_desc)
        print(arg_list)

        # test for accessibility
        access = ""
        s_public = re.search(r'public\s{0,10}?:', header_code)
        public_begin = 0
        if s_public is not None:
            public_begin = s_public.end()

        s_protected = re.search(r'protected\s{0,10}?:', header_code)
        protected_begin = 0
        if s_protected is not None:
            protected_begin = s_protected.end()

        s_private = re.search(r'private\s{0,10}?:', header_code)
        private_begin = 0
        if s_private is not None:
            private_begin = s_private.end()

        s_func = re.search(r'\s+' + func_name + '\s{0,10}?[(]', header_code)
        if s_func is not None:
            func_begin = s_func.start()

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

        FuncInfo = namedtuple('FuncInfo', 'inline static return_type name desc arg_list return_desc return_unit return_range accessibility')
        func = FuncInfo(inline=inline_function, static=static_function, return_type=return_type, name=func_name, desc=func_desc, arg_list=arg_list,
                        return_desc=return_desc, return_unit=return_unit, return_range=return_range, accessibility=access)
        func_list.append(func)

    print(func_list)
    return func_list
