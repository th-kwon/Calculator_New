#include "stdafx.h"
#include "Calculator_base.h"

CCalculator::CCalculator()
{
	Initialize();
}

CCalculator::~CCalculator()
{
}

void CCalculator::Initialize()
{
	_question.clear();
	_vecNumbers.clear();
	_vecOperators.clear();
	_answer = 0;
	_errorCode = 0;
	_length = 0;
}

int CCalculator::Calculate()
{
	// TODO : 에러 처리
	if (_question.empty()) return -1;

	if (parseQuestion() != 0) return -1;

	map<int, wstring> currentNumbers; // 연산할 숫자 3개를 저장
	map<int, int> currentOperators; // 연산할 연산자 2개를 저장

	auto itNumber = _vecNumbers.begin();
	auto itOperator = _vecOperators.begin();

	// 첫번째 값을 입력
	if (currentNumbers[0].empty()) currentNumbers[0] = to_wstring(*(itNumber++));

	while (itNumber != _vecNumbers.end())
	{
		for (int i = 0; i <= 1; i++)
		{
			// 연산자&값을 입력
			if (currentOperators[i] == CALC_OP_UNKNOWN) currentOperators[i] = *(itOperator++);
			if (currentNumbers[i + 1].empty()) currentNumbers[i + 1] = to_wstring(*(itNumber++));

			if (itOperator == _vecOperators.end())
			{
				if (itNumber == _vecNumbers.end()) break; // 숫자, 연산자 전부 입력이 완료되었으면 종료
				else // 연산자 끝났는데 숫자만 남은 경우 : error
				{
					setError(CALC_ERROR_BAD_INPUT);
					return -1;
				}
			}
			else if (itNumber == _vecNumbers.end()) // 숫자는 끝났는데 연산자만 남은 경우 : error
			{
				setError(CALC_ERROR_BAD_INPUT);
				return -1;
			}

		}

		// 항목 전부 체크할때까지 연산
		if (calculate_Sub(currentNumbers, currentOperators) != 0)
			return -1;
	};

	if (!currentNumbers[1].empty()) // 아직 연산할게 남아있다면 마지막으로 한번 더 연산을 돌림
		if (calculate_Sub(currentNumbers, currentOperators) != 0)
			return -1;

	_answer = std::stof(currentNumbers[0].c_str());

	return 0;
}

int CCalculator::calculate_Sub(map<int, wstring>& numbers, map<int, int>& operators)
{
	// * 2개의 연산자와 세개의 값을 받아 연산
	// * 첫번째 연산자가 *, /일 경우 : 첫번째와 두번째 항목을 바로 계산
	// * 첫번째 연산자가 +, -일 경우 : 두번째 연산자를 체크
	//   - 두번째 연산자가 +, -일 경우 : 첫번째와 두번째 항목을 계산
	//   - 두번째 연산자가 *, /일 경우 : 두번째와 세번째 항목을 계산, 이후 두번째 연산자를 다시 체크

	switch (operators[0])
	{
	case CALC_OP_PLUS:
	case CALC_OP_MINUS:
	{
		// +, -에 대한 처리
		switch (operators[1])
		{
		case CALC_OP_MULTIPLY:
		case CALC_OP_DIVIDE:
		{
			// +, -가 나온 뒤 *, / : 뒤의 두개만 계산함
			double result = 0;
			if (calculate_Simple(std::stof(numbers[1].c_str()), std::stof(numbers[2].c_str()), operators[1], result) != 0)
				return -1;
			// 이후 결과값 처리
			numbers[1] = to_wstring(result);
			operators[1] = CALC_OP_UNKNOWN;
			numbers[2].clear();
		}
		break;
		case CALC_OP_PLUS:
		case CALC_OP_MINUS:
		default: // 뒤의 항이 비었을 때에도 처리
		{
			// +, -가 나온 뒤 한번 더 +, - : 앞의 두개만 바로 계산하고, 뒤는 남겨둠
			double result = 0;
			if (calculate_Simple(std::stof(numbers[0].c_str()), std::stof(numbers[1].c_str()), operators[0], result) != 0)
				return -1;
			// 이후 결과값 처리
			numbers[0] = to_wstring(result);
			// 뒤의 연산을 앞으로 당김
			operators[0] = operators[1];
			operators[1] = CALC_OP_UNKNOWN;
			numbers[1] = numbers[2];
			numbers[2].clear();
		}
		break;
		}
	}
	break;
	case CALC_OP_MULTIPLY:
	case CALC_OP_DIVIDE:
	{
		// *, /에 대한 처리
		// 첫 연산자라면 앞의 두개만 바로 계산하고, 뒤는 남겨둠
		double result = 0;
		if (calculate_Simple(std::stof(numbers[0].c_str()), std::stof(numbers[1].c_str()), operators[0], result) != 0)
			return -1;
		// 이후 결과값 처리
		numbers[0] = to_wstring(result);
		// 뒤의 연산을 앞으로 당김
		operators[0] = operators[1];
		operators[1] = CALC_OP_UNKNOWN;
		numbers[1] = numbers[2];
		numbers[2].clear();
	}
	break;
	}

	return 0;
}

int CCalculator::calculate_Simple(double input1, double input2, int operation, double & result)
{

	switch (operation)
	{
	case CALC_OP_PLUS:
		result = input1 + input2;
		break;
	case CALC_OP_MINUS:
		result = input1 - input2;
		break;
	case CALC_OP_MULTIPLY:
		result = input1 * input2;
		break;
	case CALC_OP_DIVIDE:
		if (input2 == 0)
		{
			// 0으로 나눴을 때의 오류
			setError(CALC_ERROR_DIV_BY_ZERO);
			return -1;
		}
		result = input1 / input2;
		break;
	default:
		// 기타 연산에러
		setError(CALC_ERROR_UNKNOWN_OPERATION);
		return -1;
		break;
	}


	return 0;
}


int CCalculator::parseQuestion()
{
	// * 문장을 앞부터 한글자씩 읽어가며 숫자 부분, 연산자 부분을 구분해 저장
	//   - 숫자 및 .이 나올 경우 : 숫자 부분에 값을 기억
	//   - 연산자가 나올 경우 : 기억한 숫자값을 벡터로 저장
	//   - (가 나올 경우 : 클래스를 재귀호출해 답을 읽어와 숫자로 저장
	//   - )가 나오거나 문장이 끝난 경우 : 지금까지 저장한 값을 연산

	wstring numberInput; // 입력받은 숫자의 임시 저장소
	int length = 0; // 문장의 길이 - 처리한 내용의 길이를 저장하기 위해 사용


	for (auto it = _question.begin(); it != _question.end(); ++it)
	{
		switch (*it)
		{
		case '+':
		case '-':
		case '*':
		case '/':

		{
			// 연산자 전까지 확인한 값을 집어넣음
			if (numberInput.empty())
			{
				setError(CALC_ERROR_BAD_INPUT);
				return -1;
			}
			double newNumber = std::stof(numberInput.c_str());
			_vecNumbers.push_back(newNumber);
			numberInput.clear();


			// 현재 연산자 정보를 저장
			switch (*it)
			{
			case '+': _vecOperators.push_back(CALC_OP_PLUS); break;
			case '-': _vecOperators.push_back(CALC_OP_MINUS); break;
			case '*': _vecOperators.push_back(CALC_OP_MULTIPLY); break;
			case '/': _vecOperators.push_back(CALC_OP_DIVIDE); break;

			}
		}
		break;
		case '(':
		{
			wstring Question2 = _question.substr(length + 1, _question.length() - length - 1);		//Question2 에 괄호 내용 삽입

			CCalculator Calculator2;					// 클래스 호출
			int Length2 = 0;							// 괄호 안 내용 길이
			Calculator2.SetQuestion(Question2);			// 새클래스 SetQuestion에 question를 대입
			Calculator2.Calculate();					// 괄호 안 내용 연산

			numberInput = to_wstring(Calculator2.GetAnswer());		// 연산 결과를 numberInput에 삽입

			Length2 = Calculator2.GetLength();			// Length2에 괄호 안 내용의 길이를 삽입
			length += Length2 + 1;						// 괄호 밖 length에 괄호 안의 길이를 삽입

			if (length >= _question.length()) {		// 남은 연산이 없을경우
				it = _question.end() - 1;
			}
			else {										// 남은 연산이 많은경우
				it += Length2 + 1;
			}
			break;
		}
		case ')': //)가 나오거나 문장이 끝난 경우 : 지금까지 저장한 값을 연산
		{
			double newNumber = std::stof(numberInput);

			_vecNumbers.push_back(newNumber);
			numberInput.clear();
			_length = length;

			return 0;

			break;
		}
		default:
		{
			// 기타 숫자 및 . 입력시에 대한 처리
			char letter = *it;
			if (isdigit(letter) || letter == '.') // 숫자 혹은 .이라면 글자 추가
			{
				numberInput.append(1, letter);
			}
			else if (letter != ' ') // 공백이라면 패스, 그 외에는 에러 처리
			{
				setError(CALC_ERROR_BAD_INPUT);
				return -1;

			}
		}
		break;
		}

		length++; // 처리한 문장의 길이 기록

	}

	// 마지막 숫자를 기록

	double newNumber = std::stof(numberInput.c_str());

	_vecNumbers.push_back(newNumber);
	numberInput.clear();
	_length = length;

	return 0;
}