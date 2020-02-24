#pragma once
#include <string>
#include <vector>
#include <map>

using namespace std;

class CCalculator
{
public:
	CCalculator();
	~CCalculator();

	enum {
		CALC_OP_UNKNOWN = 0,
		CALC_OP_PLUS = 1,
		CALC_OP_MINUS = 2,
		CALC_OP_MULTIPLY = 3,
		CALC_OP_DIVIDE = 4
	}; // 연산자 enum
	enum { CALC_ERROR_UNKNOWN_OPERATION = 1, CALC_ERROR_DIV_BY_ZERO, CALC_ERROR_BAD_INPUT }; // 에러 enum

	void SetQuestion(wstring question) { Initialize();  _question = question; };
	double GetAnswer() { return _answer; };
	int GetError() { return _errorCode; };
	int GetLength() { return _length == 0 ? _question.length() : _length; } // 연산한 항목의 길이를 반환.(재귀호출 체크용) 아직 연산을 수행하지 않았다면 질의 전체의 길이를 반환
	void Initialize(); // 내용을 초기화
	int Calculate(); // 연산 함수. 성공시 0을, 실패시 -1을 리턴

protected:
	wstring _question; // 연산 문장을 넣는 변수
	double _answer; // 결과값을 넣는 변수
	vector<double> _vecNumbers; // 각 항목 숫자를 넣는 벡터
	vector<int> _vecOperators; // 연산자를 저장하는 벡터

	int _errorCode; // 연산 결과 성공여부 - 0:성공, 1:실패, 기타 숫자 : 에러 종류.(div/0 등)
	int _length; // 연산한 문장 길이 체크용

private:
	int calculate_Sub(map<int, wstring>& numbers, map<int, int>& operators); // 3개의 항을 받아 연산하는 함수. 성공시 0을, 실패시 -1을 리턴
	int calculate_Simple(double input1, double input2, int operation, double& result); // 단순 두 항을 연산하는 함수. 성공시 0을, 실패시 -1을 리턴
	void setError(int errorCode) { _errorCode = errorCode; };
	int parseQuestion(); // 문장을 값과 연산자로 구분
};