# Calculator
Calculating application with C++ MFC, Using class named calculator

### public 함수

```
enum {
		CALC_OP_UNKNOWN = 0,
		CALC_OP_PLUS = 1,
		CALC_OP_MINUS = 2,
		CALC_OP_MULTIPLY = 3,
		CALC_OP_DIVIDE = 4
	}; 
  enum { CALC_ERROR_UNKNOWN_OPERATION = 1, CALC_ERROR_DIV_BY_ZERO, CALC_ERROR_BAD_INPUT };
```

 연산자를 수식에 쓰기위해 임시적으로 int형으로 저장
 
 에러 및 unknown도 따로 저장
 
```
void SetQuestion(wstring question) { Initialize();  _question = question; };
```

* 연산 문장을 세팅합니다.

    - 입력값 : 연산문장 question(wstring)
    
    - 출력값 : 없음(void)
    
   + 작동 로직
    
        - Initialize()을 사용하여 내용을 초기화 합니다.
        
        - 초기화된 question에 입력값을 대입시킵니다.

```
double GetAnswer() { return _answer; };
```

* 출력하기위한 결과값을 받아옵니다.

    - 입력값 : 없음

    - 출력값 : 결과값(double)
    
   + 작동 로직
   
      - 실행시 결과값인 _answer를 리턴합니다.
```
int GetError() { return _errorCode; };
```

* 연산 결과의 성공 여부를 반환합니다.

  - 입력값 : 없음
  
  - 출력값 : 연산 결과(int)
  
  -작동 로직
  
    + errorCode 값을 리턴합니다.
    
    + 연산 성공시 0, 실패시 1, 그외 에러엔 기타 숫자 : 에러종류(ex. dib/0)값을 리턴합니다.

```
int GetLength() { return _length == 0 ? _question.length() : _length; }
```

* 연산한 항목의 길이를 리턴

    - 입력값 : 없음
  
    - 출력값 : 연산한 길이(Int);
    
   - 작동 로직
   
      - _length 값을 반환합니다.
      
      - _length 값은 연산 도중 parseQuestion() 함수의 작업이 끝나면 저장됩니다.
      
      - _length 값이 0이면 식 전체의 길이를 반환합니다.(아직 연산을 하지 않은 상태임)

```
void Initialize();
```

* 내용을 초기화합니다.

  - 입력값 : 없음
  
  - 출력값 : 없음(void)
  
 + 작동 로직
    
    - 작동시 question, vecNumber, vecOperators , answer, errorCode, length를 초기화합니다.

```
int Calculate();
```

* 기본 연산함수 

  - 입력값 : 없음
  
  - 출력값 : 연산 성공여부(int)
  
  + 작동 로직
  
      - 연산자 map currentOperators와 숫자 map currentNumbers를 읽습니다.
      
      - 연산자와 숫자를 하나씩 사용하여 다 사용할때까지 연산합니다.
      
      - 결과값은 _answer에 저장합니다.
      
      - 숫자 혹은 연산자가 남는경우 error 발생합니다.
  
      - 연산 성공시 0, 실패시 1 을 리턴합니다.


### protect 변수
```
	 wstring _question;
```
  * 연산문장을 넣는 변수
```
	double _answer;
```
  * 결과값을 넣는 변수
```
	vector<double> _vecNumbers; 
```
  * 각 항목 숫자를 넣는 벡터
```	
  vector<int> _vecOperators;
```  
  * 연산자를 저장하는 벡터
```
	int _errorCode;
```  
  * 연산 결과 성공여부 - 0:성공, 1:실패, 기타 숫자 : 에러 종류.(div/0 등)
```  
	int _length; 
```  
  * 연산한 문장 길이 체크용

### private 함수

```
  int calculate_Sub(map<int, wstring>& numbers, map<int, int>& operators); 
```

   * 3개의 항을 받아 연산하는 함수
   
        - 입력값 : 값 배열 numbers/ 연산자 배열 operators
        
        - 출력값 : 연산 성공여부(int)
        
      + 작동 로직
      
        - map 합수를 이용하여 numbers와 operators를 정의합니다.
      
        - 2개의 연산자와 3개의 값을 받아 연산합니다.
        
        - 2번째까지의 연산자중 *, / 가 있으면 그것을 우선, 아닌경우 순서대로 연산합니다.

        - 연산 성공시 0. 실패시 1 을 리턴한다.
        
        
```
	int calculate_Simple(double input1, double input2, int operation, double& result); 
```

  * 단순 두 항을 연산하는 함수
    
      - 입력값 : 계산되는수 input1, input2 / 연산자 operation / 결과값 result
        
      - 출력값 : 연산 성공여부(int)
        
      * 작동 로직
       
         - operation 값에 따라 input1 과 input2를 연산하고 결과값을 result에 저장합니다.
       
         - 연산 성공시 0, 실패시 1을 리턴한다.

```
	void setError(int errorCode) { _errorCode = errorCode; };
```

  * errorCode 를 세팅하는 함수
    
      - 입력값 : errorCode(int)
      
      - 출력값 : 없음(void)
      
     + 작동 로직
     
       - 입력받은 errorCode 값을 _errorCode에 저장합니다.
       
```
	int parseQuestion();
```

   * 문장을 값과 연산자로 구분
   
      - 입력값 : 없음
      
      - 출력값 : 숫자, 연산자 (Int)
      
     + 작동 로직
     
      - 입력받은 숫자,연산자를 구분해서 저장합니다.
        
      - 연산자가 나올 때마다 _vecNumbers에 숫자를 _vecOperators에 연산자를 push back 합니다.
	
      - 문장의 길이를 length++ 를 이용해 기록합니다.
	
	-
## Dlg

```
CString question; 
```

 - 연산 문장 전체를 저장하는 문자열

```
CString answer;
```

 - 연산 결과값 저장용 문자열


```
wstring wsQestion(question)
```

 - question을 wstring 형식으로 따로 저장
	
```
CCalculator calc
```

 - 헤드에있는 CCalculator 함수를 calc라는 이름으로 불러옴
	
```
calc.SetQuestion(wsQuestion) 
```

 - 헤드에있는 SetQuestion에 wsQuestion을 대입함

```
 if (clac.Calculate() !=0)
 ```
 
  - 리턴값이 0이 아닐때 즉 에러일 경우
  
 ```
 switch(calc.GetError()) 
 ```
 
  - 에러의 종류를 찾기위한 스위치함수
  
 ```
 case CCalculator::CALC_ERROR_BAD_INPUT:
 answer = L"입력오류"
 ```
 
  - 입력 오류일경우 결과값으로 입력오류! 를 결과값에 저장
  
  ```
  case CCalculator::CALC_ERROR_DIV_BY_ZERO
  answer= L"0으로 나눌 수 없습니다"
  ```
  
   - 0으로 숫자를 나눌경우 0으로 나눌 수 없습니다 를 결과값에 저장
   
 ```
   default:
   	answer =L"계산오류";
	break;
```

 - 그 외에 다른 오류일경우 계산오류 를 결과값에 저장
 
 ```
 else answer.Format(L"%g", calc.GetAnswer());
 ```
 
  - 에러가 없을 경우 결과값을 answer에 저장
  
  ```
  SetDlgTemText(IDC_EDIT, answer)
  ```
  
   - 최종 결과값을 컨트롤박스 IDC_EDIT_ANSWER에 저장 출력
   
## base.cpp

```
CCalculator::CCalculaor()
{
	Initialize();
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
```

 * CCalculator 는 Initialize를 사용하는 함수

 * Initialize는 전 기록이 남지 않도록 question, vecNumber, vevOperators, answer, errorCode, length를 모두 초기화하는 함수
 
### int CCalculator::Calculate()
---------------------------------
 
```
if (_question.empty()) return -1;

if (parseQuestion() != 0) return -1;
```
 
 * question 또는 parseQuestion이 잘못된값을 리턴할경우 에러 처리
 
```
map<int, wstring> currentNumbers;
map<int, int> currentOperators; 
```

 * map 배열을 이용하여 numbers는 연산할 숫자3개를 저장, Operators는 연산할 연산자 2개를 저장
 
```
auto itNumber = _vecNumbers.begin();
auto itOperator = _vecOperators.begin();
```

 * inNumber는 vecNumber의 첫값이므로 첫번째 숫자
 
 * itOperator는 vecOperators의 첫값이므로 첫번째 연산자
 
```
if (currentNumbers[0].empty()) currentNumbers[0] = to_wstring(*(itNumber++));
```

 * currentNumbers의 첫번째값이 비어있을경우 itNumber의 값으로 설정함
 
 * currentNumbers에 첫번째 값을 입력하는 조건문
 
```
while (itNumber != _vecNumbers.end())
```

 * itNumber 가 vecNumbers의 끝자리와 다른동안 반복한다
 
```
for (int i = 0; i <= 1; i++)
{
	
	if (currentOperators[i] == CALC_OP_UNKNOWN) currentOperators[i] = *(itOperator++);
	if (currentNumbers[i + 1].empty()) currentNumbers[i + 1] = to_wstring(*(itNumber++));
```	

 * currentOperators와 currentNumbers에 각각 연산자와 숫자를 입력한다

```
if (itOperator == _vecOperators.end())
{
	if (itNumber == _vecNumbers.end()) break;
```

 * 숫자와 연산자를 모두사용하면 연산이 종료됨
 
 ```
	else 
	{
		setError(CALC_ERROR_BAD_INPUT);
		return -1;
	}
}
```
 
 * 연산자 끝났는데 숫자가 남은경우 ErrorCode 발생

```
	else if (itNumber == _vecNumbers.end())
	{
		setError(CALC_ERROR_BAD_INPUT);
		return -1;
	}

}
```
 * 숫자가 끝났는데 연산자가 남은경우 ErrorCode 발생

```
if (calculate_Sub(currentNumbers, currentOperators) != 0)
		return -1;
};
```

 * 항목을 전부 체크할 때까지 연산한다.
 
 ```
 if(!currentNumbers[1].empty()) // 아직 연산할게 남아있다면 마지막으로 한번 더 연산을 돌림
		if (calculate_Sub(currentNumbers, currentOperators) != 0)
			return -1;
```

 * 연산할게 남아있다면 마지막으로 한번 더 연산함
 
 
 ```
 _answer = std::stof(currentNumbers[0].c_str());
 
 return 0;
 ```
 
  * 결과값을 float 형으로 저장한다
  
  * 전부 끝나면 0을 리턴한다.
  
## int CCalculator::calculate_Sub(map<int, wstring>& numbers, map<int, int>& operators)
--------------------------------
숫자3개 연산자 2개 이상일때 사용하는 수식

```
switch(operators[0])
	{
	case CALC_OP_PLUS:
	case CALC_OP_MINUS:
	{
	switch (operators[1])
		{
		case CALC_OP_MULTIPLY:
		case CALC_OP_DIVIDE:
		{
		double result = 0;
			if (calculate_Simple(std::stof(numbers[1].c_str()), std::stof(numbers[2].c_str()), operators[1], result) != 0)
				return -1;
```

 * 첫 연산자가 +,-이고 뒤에 연산자가 *,/ 일 경우
 
 * number[0]은 놔두고 number[1]과 number[2]먼저 연산한다.
 
 * 이상한 값이 나올경우 -1을 리턴한다.
 
 ```
 	numbers[1] = to_wstring(result);
			operators[1] = CALC_OP_UNKNOWN;
			numbers[2].clear();
		}
```

 * 위에 number[1]과 number[2]의 연산결과값을 number[1]에 저장한다.
 
 * 더 사용하지 않을 operator[1]과 number[2]를 각각 unknown과 null로 만든다.
 
```
case CALC_OP_PLUS:
case CALC_OP_MINUS:
	default: 
```

* 1번째가 +,-이고 2번째가 *,/를 제외한 나머지일 경우

```
double result = 0;
	if (calculate_Simple(std::stof(numbers[0].c_str()), std::stof(numbers[1].c_str()), operators[0], result) != 0)
		return -1;
numbers[0] = to_wstring(result);
	operators[0] = operators[1]; 
	operators[1] = CALC_OP_UNKNOWN;
	numbers[1] = numbers[2];
	numbers[2].clear();
	}
```

* number[0]과 number[1]을 operator[0]대로 연산한다

* number[2]와 operators[1]은 다음 연산을 위해 사용하지 않는다.

 ## int CCalculator::calculate_Simple(double input1, double input2, int operation, double & result)
-----------------------------------------------

1대1 상황에서의 연산

```
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
```

 * opration, 연산자의 모양대로 값1과 값2의 +,-,*,/ 연산을 싱행한다
 
 * 연산 값은 result에 삽입힌다.
 
 * 0으로 나눌경우 ErrorCode 발생한다
 
 ```
 default:
	// 기타 연산에러
	setError(CALC_ERROR_UNKNOWN_OPERATION);
	return -1;
	break;
	}
return 0;
}
```

 * 그 외 Operator에 이상한값이 들어갔을경우 ERROR CODE발생
 
 * 이경우엔 -1을 리턴한다
 
 ```
 int CCalculator::parseQuestion()
 ```
 
 * 문장을 앞에서부터 읽어가며 연산자가 나올때마다 숫자,연산자를 구분해 저장
 
 ```
 string numberInput;
 Int length = 0;
 ```
 
  * numberInput은 입력받은 수의 임시 저장소
  length 는 문장의 길이
  
 ```
 switch (*it)
		{
		case '+':
		case '-':
		case '*':
		case '/':

		{
			// 연산자 전까지 확인한 값을 집어넣음
			double newnumber = atof(numberInput.c_str());
			_vecNumbers.push_back(newnumber);
			numberInput.clear();
```

 * 연산자가 +,-,*,/중 하나일때 작동함
 
 * 연산자 전까지 확인한 값을 저장
 
 ```
 switch (*it)
	{
	case '+': _vecOperators.push_back(CALC_OP_PLUS); break;
	case '-': _vecOperators.push_back(CALC_OP_MINUS); break;
	case '*': _vecOperators.push_back(CALC_OP_MULTIPLY); break;
	case '/': _vecOperators.push_back(CALC_OP_DIVIDE); break;
```

 * 위에서입력한 연산자를 vecOperator에 저장

```
default:
	{
		char letter = *it;
		if (isdigit(letter) || letter == '.')
		{
			numberInput.append(1, letter);
		}
		else if (letter != ' ')
		{
			setError(CALC_ERROR_BAD_INPUT);
			return -1;
		}
	}
```

 * 기타숫자 혹은 .이라면 글자 추가
 
 * 공백은 아무일도 일어나지 않으며 그외에 문자가 추가되면 ErrorCode 발생
 
 ```
 length++; 
newnumber = atof(numberInput.c_str());
_vecNumbers.push_back(newnumber);
numberInput.clear();
_length = length;
return 0;
```
 * 반복작업이 끝나고 마지막 연산을 하는 코드

 * 반복문이 한번 돌아갈때마다 length가 1씩 증가하여 문장의 길이를 기록함
 
 * newNumber는 numberInput(임시저장소)의 float형 변환
 
 * float형으로 변경된 newNumber를 vecNumber 에 삽입하고 임시저장소인 number_Input을 초기화
 
 * 길이체크용 변수인 _length에 length값을 대입
 
 * 모든 연산이 완료되면 성공의 의미인 0을 리턴
