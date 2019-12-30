#include "python.h" 

struct Test {
	int a;
	int b;
	char* c;
};
static PyObject*
extest_sfn(PyObject* self, PyObject* args)
{
	struct Test* p;
	if (!PyArg_ParseTuple(args, "L", &p)) // �Ű����� ���� �м��ϰ� ���������� �Ҵ� ��ŵ�ϴ�.
		return NULL;
	printf("a=%d b=%d c=%s\n", p->a, p->b, p->c);
	p->a = 100;
	p->b = 200;
	return Py_BuildValue("(i,i)", p->a, p->b);  //python type conversion..
}

static PyObject*  
extest_strlen(PyObject* self, PyObject* args)
{
	const char* str = NULL;
	int len;
	if (!PyArg_ParseTuple(args, "s", &str)) // �Ű����� ���� �м��ϰ� ���������� �Ҵ� ��ŵ�ϴ�.
		return NULL;
	len = strlen(str);
	return Py_BuildValue("i", len);  //python type conversion..
}

static PyObject*
extest_hap(PyObject* self, PyObject* args)
{
	int a;
	int b;
	int sum;
	if (!PyArg_ParseTuple(args, "ii", &a, &b) ) // �Ű����� ���� �м��ϰ� ���������� �Ҵ� ��ŵ�ϴ�.
		return NULL;
	sum = a+b;
	return Py_BuildValue("i", sum);  //python type conversion..
}

static PyObject*
extest_circle(PyObject* self, PyObject* args)
{
	int r;
	double cArea;
	if (!PyArg_ParseTuple(args, "i", &r) ) // �Ű����� ���� �м��ϰ� ���������� �Ҵ� ��ŵ�ϴ�.
		return NULL;
	cArea = r*r*3.14;
	return Py_BuildValue("d", cArea);  //python type conversion..
}
static PyObject*
extest_fn(PyObject* self, PyObject* args)
{
	int a;
	int b;
	if (!PyArg_ParseTuple(args, "ii", &a,&b)) // �Ű����� ���� �м��ϰ� ���������� �Ҵ� ��ŵ�ϴ�.
		return NULL;
	return Py_BuildValue("(i,i)", a,b);
	//return Py_BuildValue("[i,i]", a, b);
	//return Py_BuildValue("{i:i}", a, b);
}
static PyMethodDef extestMethods[] = {
{"strlen", extest_strlen, METH_VARARGS,
 "count a string length."},
{"hap", extest_hap, METH_VARARGS,
 "int hap."},
{"circle", extest_circle, METH_VARARGS,
 "circle."},
{"fn", extest_fn, METH_VARARGS,
 "fn."},
{"sfn", extest_sfn, METH_VARARGS,
 "fn."},
 {NULL, NULL, 0, NULL} // �迭�� ���� ��Ÿ���ϴ�.
};

static struct PyModuleDef extestmodule = {
	PyModuleDef_HEAD_INIT,
	"extest",            // ��� �̸�
	"It is test module.", // ��� ������ ���� �κ�, ����� __doc__�� ����˴ϴ�.
	-1,extestMethods
};

PyMODINIT_FUNC
PyInit_extest(void)
{
	return PyModule_Create(&extestmodule);
}




