// 1_후위반환타입

/*
int square(int a)
{
	return a * a;
}
*/
// 후위 반환 타입(suffix return type, trailing return type) 이라는 문법
// C++11 부터 도입된 문법
auto square(int a) -> int
{
	return a * a;
}


int main()
{
	square(3);
}