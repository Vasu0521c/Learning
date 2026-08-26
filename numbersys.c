#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

#define TRUE 1
#define FALSE 0

void test();
void choice();
int is_same(char *actual_value, char *expect_value);

char* compliment_1(char *input_number);
char* compliment_2(char *input_number);
                     
void input(char *input_number, int *length);
char* sign_or_unsign(char *input_number, char s);
char* input_and_decide_type(char *input_number);

int is_binary(int len, char *num);
int char_to_int(int len, char *num);
int get_result(int val);
int get_length(char *str);

char* binary_to_octal(char *input_number);
char* binary_to_decimal(int length, char *num);
char* binary_to_hex(char *input_number);

char* decimal_to_binary(int val);
char* decimal_to_octal(char *input_value);
char* decimal_to_hex(char *input_value);

char* octal_to_binary(char *input_number);
char* octal_to_decimal(char *input_number);
char* octal_to_hex(char *input_number);

char* single_hex_to_binary(char input);
char* multi_hex_to_binary(char *input_value);
char* hex_to_octal(char *input_number);
char* hex_to_decimal(char *input_number);


int get_result (int val) {

	int result = 0;
	while (val > 0) {
		val /= 10;
		result++;
	}
	return result;
}

int get_length (char *str) {
	int i = 0;
	if (str == NULL) 
		return i;
	while (str[i] != '\0') {
		i++;
	}
	return i;
} 

int is_same (char* actual_value, char* expect_value) {
	
	int i = 0;
    int length_av = get_length (actual_value);
    int length_ev = get_length (expect_value);
  	if (length_av != length_ev)
		return FALSE;

	if (actual_value == NULL || expect_value == NULL) {
		return FALSE;
	}
	while (expect_value[i] != '\0') {
		if (actual_value[i] != expect_value[i]) {
			return FALSE;
		}
		i++;
	}
	return TRUE;
}

char* compliment_1(char *input_number) {


	int len = get_length(input_number);
	int i = 0;
	char *result = malloc (len + 2);
	while (i < len) {
		if (input_number[i] == '0') {
			result[i] = '1';
		}
		else {
			result[i] = '0';
		}
		i++;
	}
	return result;
}

char* compliment_2(char *input_number) {

	int len = get_length(input_number) - 1;
	char bit_v = '1';
	char *result = malloc (len + 2);
	result = compliment_1(input_number);

	while (len >= 0) {
		if(result[len] == '0') {
			if(bit_v == '1') {
				result[len] = '1';
				bit_v = '0';
			}
		}
		else {
			if(bit_v == '1') {
				result[len] = '0';
			}
		}
		len--;
	}
	return result;
}

int is_binary (int len, char* num) {

	for (int i = 0; i < len; i++) {
		if (num[i] != '1' && num[i] != '0') {
			printf ("Given input is not binary.\n");
			return 1;
		}
	}
	return 0;
}


int char_to_int (int len, char *num) {
	int value = 0;
	for (int i = 0; i < len; i++) {
		if (num[i] == '\0') {
			break;
		}
		if (num[i] == '-') {
			continue;
		}
		value = (value * 10) + (num[i] - '0');
	}
	return value;
}

void input (char* input_number, int* length) {

	printf ("Enter Values : ");
//	char c;
//	while ( (c = getchar()) != '\n' && c != EOF && c != '\0');

	fgets (
		input_number, 
		*length,
		stdin
	);

	for (int i = 0; i < 1024; i++) {
		if (input_number[i] == '\n') {
			input_number[i] = '\0';
			*length = i;
			break;
		}
	}
	printf ("Entered Number: %s\n", input_number);
	printf ("length: %d\n", *length);
}

char* sign_or_unsign(char *input_number, char s) {

	char *result  = malloc (5);
	if(s == '0') {
		result = binary_to_decimal(4, input_number);
		return result;
	}
	else {
		if(input_number[0] == '0') {
			result = binary_to_decimal(3, input_number+1);
			return result;
		}
		else {
			result = binary_to_decimal(4, compliment_2(input_number));
		}
	}
	return result;
}

void all_right(char sign, char *input_number) {

	if (sign != '-') {
		sign = '\0';
	}
	int len = get_length(input_number);
	printf("Given value in binary  : %c0b%s\n", sign, input_number);
	printf("Given Value in Octal   : %c0%s\n", sign, binary_to_octal(input_number));
	printf("Given value in decimal : %c%s\n", sign, binary_to_decimal(len, input_number));
	printf("Given value in hex     : %c0x%s\n", sign, binary_to_hex(input_number));
	return;
}

char* binary_to_octal(char *input_number) {

	int len = get_length(input_number);
	char *result = malloc(len + 1);
	if (len <= 1 && input_number[0] == '0') {
		result[0] = '0';
		return result;
	}
	int k = 0;
	int i = len - 1;
	while (i >= 0) {
		int value = 0;
		for (int j = 0; j < 3; j++) {
			if(i < 0) {
				break;
			}
			if(input_number[i] == '1') {
				value += 1 << j;
			}
			i--;
		}
		result[k] = value + '0';
		k++;
	}
	len = get_length(result) - 1;
	i = 0;
	while (i < len) {
		char c      = result[i];
		result[i]   = result[len];
		result[len] = c;
		i++;
		len--;
	}
	return result;
	
}



char* binary_to_hex(char *input_number) {

	int len = get_length(input_number);
	char *result = malloc(len + 1);
	result[len] = '\0';
	int k = 0;
	int i = len - 1;
	if(len < 1 && input_number[i] == '0') {
		result[0] = '0';
		return result;
	}
	while (i >= 0) {
		int value = 0;
		for(int j = 0; j < 4; j++) {
			if(i < 0) {
				break;
			}
			if(input_number[i] == '1') {
				value += 1 << j;
			}
			i--;
		}
		if(value >= 10 && value <= 15) {
			result[k] = value + 'A' - 10; 
		}
		else {
			result[k] = value + '0';
		}
		k++;
	}
	len = get_length(result) - 1;
	int ll = len;
	i = 0;
	while(i < len) {
		char x = result[i];
		result[i] = result[len];
		result[len] = x;
		i++;
		len--;
	}
	i = 0;
	int not_0 = 0;
	while (ll > 0 && not_0 == 0 && result[i] != '\0') {
		if (result[i] == '0') {
			result++;
		}
		else {
			not_0 = 1;
		}
		i++;
	}
	return result;
	
}

char* binary_to_decimal (int len, char* num) {

	int value = 0;
	int j = 0;
	for (int i = len-1; i >= 0; i--) {
		if (num[i] == '1') {
			value += (1 << j);
		}
		j++;
	
	}
	char *result = malloc (1024);
	j = get_result (value);
	int temp = j;
	j--;
	if (value == 0) {
		result[0] = '0';
		return result;
	}
	while (value > 0) {
		result[j] = (value % 10) + '0';
		value /= 10;
		j--;
	}
	result[temp] = '\0';
	return result;

}

char* decimal_to_binary (int value) {

	char a_binary[1024] = {};
	int count = 0;
	if (value == 0) {
		a_binary[0] = '0';
		count++;
	}
	for (int i = 0; value > 0; i++) {
		if (value % 2 == 0) {
			a_binary[i] = '0';
		}
		else {
			a_binary[i] = '1';
		}
		value /= 2;
		count++;
	}
	count--;
	char *result = malloc (1024);
	for (int i = 0; i <= count; i++) {
		result[i] = a_binary[count - i];
	}
	return result;
}

char* decimal_to_octal (char *input_value) {
	
	int len = strlen (input_value);
	int value = char_to_int (len, input_value);
	char *result = malloc (1024);
	int i = 0;
	while (value > 8) {
		result[i] = (value % 8) + '0';
		value /= 8;
		i++;
	}
	result[i] = value + '0';
	result[i+1] = '\0';
	len = strlen (result);
	for (int j = 0; j < i; j++) {
		char temp = result[j];
		result[j] = result[i];
		result[i] = temp;
		i--;
	}
	return result;
}



char* octal_to_binary (char *input_value) {
	
	int len = get_length (input_value);
	char *result = malloc ((len * 3) + 1);
	int k = 2;
	int x = 0;
	for (int i = 0; i < len; i++) {
		int value = input_value[i] - '0';
		if (value == 0) {
			result[i] = '0';
			continue;
		}
		
		x = k;
		for(int j = 0; j < 3; j++) {

			if (value % 2 == 1) {
				result[k] = '1';
			}
			else {
				result[k] = '0';
			}
			value /= 2;
			k--;

		}
		k = x + 3;
	}
	
	int i = 0;
	while (result[i] == '0' && result[i+1] != '\0') {
		i++;
	}
	return result+i;
}

char* octal_to_decimal (char *input_value) {

	int value = 0;
	int temp_var = 0;
	int len = get_length (input_value) -1;
	int j = 0;
	for (int i = len; i >= 0 ; i--) {
		temp_var = input_value[i] - '0';
		int power = (int) pow(8, j);
		value += power * temp_var;
		j++;
	}
	char *result = malloc (1024);

	if (input_value[0] == '0' && len < 1)
		result[0] = '0';
	
	len = get_result (value);
	for (int i = len-1; value > 0 ; i--) {
		result[i] = (value % 10) + '0';
		value = value / 10;
	}
	return result;
}



char* octal_to_hex (char *input_value) {
	
	int value = 0;
	input_value = octal_to_decimal (input_value);

	int len = get_length (input_value);

	for (int i = 0; i < len; i++) {
		value = (value * 10) + (input_value[i] - '0') ;
	}
	int i = 0;
	char *result = malloc (len);
	if (value == 0) {
		result [0] = '0';
		return result;
	}
	while (value > 0) {
		
		int temp = (value % 16);
		if (temp <= 9 && temp >= 0) {
			result[i] = temp + '0';
		}
		else if (temp >= 10 && temp <= 15) {
			result[i] = temp + 'A' - 10;
		}
		value /= 16;
		i++;
	}
	len = get_length (result) - 1;
	for (i = 0; i < len; i++) {
		char t         = result[i];
		result [i]     = result [len];
		result [len] = t;
		len --;
	}
	return result;

}

char* hex_to_decimal (char *input_value) {

	int value = 0;
	int temp_var = 0;
	int len = get_length(input_value) - 1;
	int j = 0;
	for (int i = len; i >= 0 ; i--) {
		if ( (input_value[i] >= 'a') && (input_value[i] <= 'f')) {
			temp_var = input_value[i] - 'a' + 10;
		}
		else if ( (input_value[i] >= 'A') && (input_value[i] <= 'F')) {
			temp_var = input_value[i] - 'A' + 10;

		}
		else {
			temp_var = input_value[i] - '0';
		}
		int power = (int) pow(16, j);
		value    += power * temp_var;
		j++;
	}
	char *result = malloc (1024);
	len = get_result (value);
	if (value == 0 && len < 1) {
		result[0] = '0';
		return result;
	}
	for (int i = len-1; value > 0 ; i--) {
		result[i] = (value % 10) + '0';
		value     = value / 10;
	}
	result[len] = '\0';
	return result;
}

char* hex_to_octal (char *input_value) {
	
	input_value = hex_to_decimal (input_value);
	int len = get_length (input_value) - 1;
	int value   = 0;
	char *result = malloc (50);

	for (int i = 0; i <= len; i++) {
		value = (value * 10) + (input_value[i] - '0'); 
	}

	int i = 0;
	int temp = 0;
	if (value == 0) {
		result[i] = '0';
	}
	while (value > 0) {
		int power = (int) pow (10, i);
		temp += ((value % 8) * power);
		value /= 8;
		i++;
	}
	
	value = temp;
	len = get_result (value);
	for (int i = len - 1; i >= 0; i--) {
		result[i] = (value % 10) + '0'; 
		value /= 10;
	}
	return result;

}

void choice () {
	int length = 1024;
	char input_number[1024] = {};

	printf ("Choose number conversion \n"
		"1.Decimal to Binary\n"
		"2.Binary to Decimals\n"
		"3.Hex to Decimal\n"
		"4.Octal to Decimal\n"
		"5.Decimal to Octal\n"
		"6.Decimal to Hex\n"
		"7.Hex to Binary\n"
		"8.Octal to Binary\n"
		"9.Hex to Decimal\n"
		"10.Octal to Decimal:"
	);

	int choice = 0;
	scanf ("%d", &choice);
	char *arr = NULL;

	switch (choice) {
		case 1:
			input (input_number, &length);
			int val = char_to_int (length, input_number);
			arr = decimal_to_binary (val);
			printf("result: %s\n", arr);
			break;
		case 2:
			input (input_number, &length);
			if (!is_binary (length, input_number)) {
				printf("result: %s\n", binary_to_decimal (length, input_number));
			}
			break;
		case 3:
			input (input_number, &length);
			arr = hex_to_decimal(input_number);
			printf("result: %s\n", arr);
			break;
		case 4:
			input (input_number, &length);
			arr = octal_to_decimal(input_number);
			printf("result: %s\n", arr);
			break;
		case 5:
			input (input_number, &length);
			arr = decimal_to_octal(input_number);
			printf("result: %s\n", arr);
			break;
		case 6:
			input (input_number, &length);
			arr = decimal_to_hex(input_number);
			printf("result: %s\n", arr);
			break;
		case 7:
			input (input_number, &length);
			arr = multi_hex_to_binary (input_number);
			printf("result: %s\n", arr);
			break;
		case 8:
			input (input_number, &length);
			arr = octal_to_binary (input_number);
			printf("result: %s\n", arr);
			break;
		case 9:
			input (input_number, &length);
			arr = hex_to_octal (input_number);
			printf("result: %s\n", arr);
			break;
		case 10:
			input (input_number, &length);
			arr = octal_to_hex (input_number);
			printf("result: %s\n", arr);
			break;
		default:
			printf ("Choose from options 1 to 10\n");
			exit (1);
	}

}


char* input_and_decide_type(char *input_number) {

	char type = 'd';
	int type_i = 1;
	if (input_number[0] == '-') {
		type_i = 2;
	}
	int len = get_length (input_number);
	if (len > 2) {
		if (input_number[type_i] == 'b' || input_number[type_i] == 'B') {
			type = 'b';
		}
		else if (input_number[type_i] == 'x' || input_number[type_i] == 'x') {
			type = 'x';
		}
		else if (input_number[type_i - 1] == '0') {
			type = 'o';
		}	
	}
	char *result = malloc (len+1);

	if(type == 'b') {
		if (type_i == 2) {
			result = compliment_2(input_number + type_i + 1);
		} else {
			result = input_number + type_i + 1;
		}
	}
	else if(type == 'o') {
		result = octal_to_binary(input_number + type_i);
	}
	else if(type == 'x') {
		result = multi_hex_to_binary(input_number + type_i + 1);
	}
	else {
		int value= char_to_int(1024, input_number + type_i - 1);
		result = decimal_to_binary(value);
	}
	return result;
}

int main () {

	test();
//	return 0;
	int length = 1024;
	char *input_number = malloc (1024);
	input(input_number, &length);



	all_right(input_number[0],input_and_decide_type(input_number));
	return 0;

}

char* decimal_to_hex (char *input_value) {

	int len = strlen (input_value);
	int value = char_to_int (len, input_value);
	char *result = malloc (1024);
	int i = 0;
	int temp = 0;
	while (value > 16) {
		temp = (value % 16);
		if ( (temp >= 10) && (temp <= 15)) {
			result[i] = 'A' + (temp - 10);
		}
		else if (temp <= 9) {
			result[i] = '0' + temp;
		}
		value /= 16;
		i++;
	}
	if ( (value >= 10) && (value <= 15)) {
		result[i] = 'A' + (value - 10);
	}
	else {
		result[i] = '0' + value;
	}
	result[i+1] = '\0';

	for (int j = 0; j < i; j++) {
		char temp_char = result[j];
		result[j]      = result[i];
		result[i]      = temp_char;
		i--;
	}

	return result;
}


void test () {
	if (!is_same (binary_to_decimal(8,"10000000"), "128")) {
		printf ("1st test failed\n");
		exit (1);
	}
	if (!is_same (binary_to_decimal(15,"100000000000000"), "16384")) {
		printf ("2st test failed\n");
		exit (1);
	}
	
	if (!is_same (binary_to_decimal(4,"1100"), "12")) {
		printf ("1st test failed\n");
		exit (1);
	}	else {
		printf ("Test 1 Passed\n");
	}
	
	if (!is_same (binary_to_decimal(4,"0110"), "6")) {
		printf ("2st test failed\n");
		exit (1);
	}	else {
		printf ("Test 2 Passed\n");
	}

	if (!is_same (binary_to_decimal(1,"0"), "0")) {
		printf ("3st test failed\n");
		exit (1);
	}	else {
		printf ("Test 3 Passed\n");
	}
			
	if (!is_same (binary_to_decimal(7,"1111011"), "123")) {
		printf ("4st test failed\n");
		exit (1);
	}	else {
		printf ("Test 4 Passed\n");
	}

	if (!is_same (binary_to_decimal(8,"11111111"), "255")) {
		printf ("5st test failed\n");
		exit (1);
	}	else {
		printf ("Test 5 Passed\n");
	}
	
	if (!is_same (hex_to_decimal("1"), "1")) {
		printf ("6th test failed\n");
		exit (1);
	}	else {
		printf ("Test 6 Passed\n");
	}

	if (!is_same (hex_to_decimal("0"), "0")) {
		printf ("6th test failed\n");
		exit (1);
	}	else {
		printf ("Test 6 Passed\n");
	}

	if (!is_same (hex_to_decimal("1330"), "4912")) {
		printf ("7th test failed\n");
		exit (1);
	}	else {
		printf ("Test 7 Passed\n");
	}

	if (!is_same (hex_to_decimal("32748"), "206664")) {
		printf ("8th test failed\n");
		exit (1);
	}	else {
		printf ("Test 8 Passed\n");
	}

	if (!is_same (hex_to_decimal("77"), "119")) {
		printf ("9th test failed\n");
		exit (1);
	}	else {
		printf ("Test 9 Passed\n");
	}

	if (!is_same (octal_to_decimal("30"), "24")) {
		printf ("10th test failed\n");
		exit (1);
	}	else {
		printf ("Test 10 Passed\n");
	}
	
	if (!is_same (octal_to_decimal("0"), "0")) {
		printf ("11th test failed\n");
		exit (1);
	}	else {
		printf ("Test 11 Passed\n");
	}
	
	if (!is_same (octal_to_decimal("1"), "1")) {
		printf ("12th test failed\n");
		exit (1);
	}	else {
		printf ("Test 12 Passed\n");
	}
	
	if (!is_same (octal_to_decimal("100"), "64")) {
		printf ("13th test failed\n");
		exit (1);
	}	else {
		printf ("Test 13 Passed\n");
	}
	
	if (!is_same (octal_to_decimal("30041"), "12321")) {
		printf ("14th test failed\n");
		exit (1);
	}	else {
		printf ("Test 14 Passed\n");
	}
	
	if (!is_same (octal_to_decimal("277"), "191")) {
		printf ("14th test failed\n");
		exit (1);
	}	else {
		printf ("Test 14 Passed\n");
	}
	
	if (!is_same (decimal_to_octal("0"), "0")) {
		printf ("15th test failed\n");
		exit (1);
	}	else {
		printf ("Test 15 Passed\n");
	}
	
	if (!is_same (decimal_to_octal("10"), "12")) {
		printf ("16th test failed\n");
		exit (1);
	}	else {
		printf ("Test 16 Passed\n");
	}
	
	if (!is_same (decimal_to_octal("1"), "1")) {
		printf ("17th test failed\n");
		exit (1);
	}	else {
		printf ("Test 17 Passed\n");
	}
	
	if (!is_same (decimal_to_octal("277"), "425")) {
		printf ("18th test failed\n");
		exit (1);
	}	else {
		printf ("Test 18 Passed\n");
	}
	
	if (!is_same (decimal_to_hex("277"), "115")) {
		printf ("19th test failed\n");
		exit (1);
	}	else {
		printf ("Test 19 Passed\n");
	}
	
	if (!is_same (decimal_to_hex("1"), "1")) {
		printf ("19th test failed\n");
		exit (1);
	}	else {
		printf ("Test 19 Passed\n");
	}

	if (!is_same (decimal_to_hex("0"), "0")) {
		printf ("20th test failed\n");
		exit (1);
	}	else {
		printf ("Test 20 Passed\n");
	}
	
	if (!is_same (decimal_to_hex("3"), "3")) {
		printf ("21th test failed\n");
		exit (1);
	}	else {
		printf ("Test 21 Passed\n");
	}
	
	if (!is_same (decimal_to_hex("399"), "18F")) {
		printf ("22th test failed\n");
		exit (1);
	}	else {
		printf ("Test 22 Passed\n");
	}
	
	if (!is_same (hex_to_octal("1"), "1")) {
		printf ("Hex - > octal test 1 failed\n");
		exit (1);
	}	else {
		printf ("Hex -> octal test 1 passed\n");
	}
	
	if (!is_same (hex_to_octal("0"), ("0"))) {
		printf ("Hex - > octal test 2 failed\n");
		exit (1);
	}	else {
		printf ("Hex -> octal test 2 passed\n");
	}
	
	if (!is_same (hex_to_octal("7"), ("7"))) {
		printf ("Hex - > octal test 3 failed\n");
		exit (1);
	}	else {
		printf ("Hex -> octal test 3 passed\n");
	}
	
	if (!is_same (hex_to_octal("1F"), ("37"))) {
		printf ("Hex -> octal test 4 failed\n");
		exit (1);
	}	else {
		printf ("Hex -> octal test 4 passed\n");
	}
	
	if (!is_same (hex_to_octal("24232"), ("441062"))) {
		printf ("Hex -> octal test 4 failed\n");
		exit (1);
	}	else {
		printf ("Hex -> octal test 4 passed\n");
	}

	if (!is_same (hex_to_octal("D"), ("15"))) {
		printf ("Hex -> octal test 5 failed\n");
		exit (1);
	}	else {
		printf ("Hex -> octall test 5 passed\n");
	}

	if (!is_same (octal_to_hex("0"), ("0"))) {
		printf ("oct -> hex test 1 failed\n");
		exit (1);
	}	else {
		printf ("oct -> hex test 1 passed\n");
	}
	
	if (!is_same (octal_to_hex("1"), ("1"))) {
		printf ("oct -> hex test 2 failed\n");
		exit (1);
	}	else {
		printf ("oct -> hex test 2 passed\n");
	}
	
	if (!is_same (octal_to_hex("3"), ("3"))) {
		printf ("oct -> hex test 3 failed\n");
		exit (1);
	}	else {
		printf ("oct -> hex test 3 passed\n");
	}

	if (!is_same (octal_to_hex("7"), ("7"))) {
		printf ("oct -> hex test 4 failed\n");
		exit (1);
	}	else {
		printf ("oct -> hex test 4 passed\n");
	}

	if (!is_same (octal_to_hex("12"), ("A"))) {
		printf ("oct -> hex test 5 failed\n");
		exit (1);
	}	else {
		printf ("oct -> hex test 5 passed\n");
	}

	if (!is_same (octal_to_hex("25"), ("15"))){
		printf ("oct -> hex test 6 failed\n");
		exit (1);
	}	else {
		printf ("oct -> hex test 6 passed\n");
	}
	
	if (!is_same (octal_to_hex("12412"), ("150A"))) {
		printf ("oct -> hex test 6 failed\n");
		exit (1);
	}	else {
		printf ("oct -> hex test 6 passed\n");
	}
	
	if(!is_same(octal_to_binary("0"), ("0"))) {
		printf("oct -> binary test 1 failed\n");
		exit(1);
	}	else {
		printf("oct -> binary test 1 passed\n");
	}
	
	if(!is_same(octal_to_binary("1"), ("1"))) {
		printf("oct -> binary test 2 failed\n");
		exit(1);
	}	else {
		printf("oct -> binary test 2 passed\n");
	}
	
	if(!is_same(octal_to_binary("00"), ("0"))) {
		printf("oct -> binary test 3 failed\n");
		exit(1);
	}	else {
		printf("oct -> binary test 3 passed\n");
	}
	
	if(!is_same(octal_to_binary("01"), ("1"))) {
		printf("oct -> binary test 4 failed\n");
		exit(1);
	}	else {
		printf("oct -> binary test 4 passed\n");
	}
	
	if(!is_same(octal_to_binary("7"), ("111"))) {
		printf("oct -> binary test 5 failed\n");
		exit(1);
	}	else {
		printf("oct -> binary test 5 passed\n");
	} 
	
	if(!is_same(octal_to_binary("15"), ("1101"))) {
		printf("oct -> binary test 6 failed\n");
		exit(1);
	}	else {
		printf("oct -> binary test 7 passed\n");
	}
	
	if(!is_same(octal_to_binary("321"), ("11010001"))) {
		printf("oct -> binary test 8 failed\n");
		exit(1);
	}	else {
		printf("oct -> binary test 8 passsed\n");
	}
	

	if (!is_same(input_and_decide_type("0b110") , "110")) {
		printf("Automate type decider test 1 failed\n");
		exit(1);
	}	else {
		printf("Type deciding test 1 passed\n");
	}
	

	if(!is_same(input_and_decide_type("0b0"),("0"))) {
		printf("Automate type decide test 2 failed\n");
		exit(1);
	}	else {
		printf("Type deciding test 2 passed\n");
	}
	
	if(!is_same(input_and_decide_type("ob1"), ("1"))) {
		printf("Automatic type decide test 3 failed\n");
		exit(1);
	}	else {
		printf("type deciding test 3 passed\n");
	}
	
	if(!is_same(input_and_decide_type("0b1111"), ("1111"))) {
		printf("Automatic type decide test 4 failed\n");
		exit(1);
	}	else {
		printf("type deciding test 4 passed\n");
	}
	
	if(!is_same(input_and_decide_type("01"), ("1"))) {
		printf("Automatic type decide test 5 failed\n");
		exit(1);
	}	else {
		printf("type deciding test 5 passed\n");
	}
	
	if(!is_same(input_and_decide_type("07"), ("111"))) {
		printf("Automatic type decide test 6 failed\n");
		exit(1);
	}	else {
		printf("type deciding test 6 passed\n");
	}
	
	if(!is_same(input_and_decide_type("015"), ("1101"))) {
		printf("Automatic type decide test 7 failed\n");
		exit(1);
	}	else {
		printf("type deciding test 7 passed\n");
	}
	
	if(!is_same(input_and_decide_type("0x0"), ("0"))) {
		printf("Automatic type decide test 8 failed\n");
		exit(1);
	}	else {
		printf("type decide test 8 passed\n");
	}
	
	if(!is_same(input_and_decide_type("0x1"), ("1"))) {
		printf("Automatic type decide test 9 failed\n");
		exit(1);
	}	else {
		printf("type decide test 9 passed\n");
	}
	
	if(!is_same(input_and_decide_type("0x10"), ("10000"))) {
		printf("type deciding test 10 failed\n");
		exit(1);
	}	else {
		printf("type decide test 10 passed\n");
	}
	
	if(!is_same(input_and_decide_type("0"), ("0"))) {
		printf("type deciding test 11 failed\n");
		exit(1);
	}	else {
		printf("type decide test 11 passed\n");
	}
	
	if(!is_same(input_and_decide_type("1"), ("1"))) {
		printf("type deciding test 12 failed\n");
		exit(1);
	}	else {
		printf("typpe decide test 12 passed\n");
	}
	
	if(!is_same(input_and_decide_type("36"), ("100100"))) {
		printf("tye decidding test 13 failed\n");
		exit(1);
	}	else {
		printf("type deciding test 13 passed\n");
 	}
 	
	if(!is_same(binary_to_octal("0"), "0")) {
		printf("bin -> octal test 1 failed\n");
		exit(1);
	}	else {
		printf("bin -> octal test 1 passed\n");
	}
	
	if(!is_same(binary_to_octal("1"), "1")) {
		printf("bin -> octal test 2 failed\n");
		exit(1);
	}	else {
		printf("bin -> octal test 2 passed\n");
	}
	
	if(!is_same(binary_to_octal("111"), "7")) {
		printf("bin -> octal test 3 failed\n");
		exit(1);
	}	else {
		printf("bin -> octal test 3 passed\n");
	}
	
	if(!is_same(binary_to_octal("1111"), "17")) {
		printf("bin -> octal test 4 failed\n");
		exit(1);
	}	else {
		printf("bin -> octal test 4 passed\n");
	}
	
	if(!is_same(binary_to_octal("1000"), "10")) {
		printf("bin -> octal test 5 failed\n");
		exit(1);
	}	else {
		printf("bin -> octal test 5 passed\n");
	}
	
	if(!is_same(binary_to_octal("111111111"), "777")) {
		printf("bin -> octal test 6 failed\n");
		exit(1);
	}	else {
		printf("bin -> octal test 6 passed\n");
	}
	
	if(!is_same(single_hex_to_binary('0'), "0000")) {
		printf("single hex -> binary test 1 failed\n");
		exit(1);
	}	else {
		printf("single hex -> binary test 1 passed\n");
	}
	
	if(!is_same(single_hex_to_binary('1'), "0001")) {
		printf("single hex -> binary test 2 failed\n");
		exit(1);
	}	else {
		printf("single hex -> binary test 2 passed\n");
	}
	
	if(!is_same(single_hex_to_binary('A'), "1010")) {
		printf("single hex -> binary test 3 failed\n");
		exit(1);
	}	else {
		printf("single hex -> binary test 3 passed\n");
	}
	
	if(!is_same(single_hex_to_binary('F'), "1111")) {
		printf("single hex -> binary test 4 failed\n");
		exit(1);
	}	else {
		printf("single hex -> binary test 4 passed\n");
	}

	if(!is_same(single_hex_to_binary('9'), "1001")) {
		printf("single hex -> binary test 5 failed\n");
		exit(1);
	}	else {
		printf("single hex -> binary test 5 passed\n");
	}

	if(!is_same(single_hex_to_binary('C'), "1100")) {
		printf("single hex -> binary test 6 failed\n");
		exit(1);
	}	else {
		printf("single hex -> binary test 6 passed\n");
	}

	if(!is_same(multi_hex_to_binary("0"), "0")) {
		printf("multi hex -> binary test 1 failed\n");
		exit(1);
	}	else {
		printf("multi hex -> binary test 1 passed\n");
	}

	if(!is_same(multi_hex_to_binary("1"), "1")) {
		printf("multi hex -> binary test 2 failed\n");
		exit(1);
	}	else {
		printf("multi hex -> binary test 2 passed\n");
	}

	if(!is_same(multi_hex_to_binary("11"), "10001")) {
		printf("multi hex -> binary test 3 failed\n");
		exit(1);
	}	else {
		printf("multi hex -> binary test 3 passed\n");
	}

	if(!is_same(multi_hex_to_binary("F1"), "11110001")) {
		printf("multi hex -> binary test 4 failed\n");
		exit(1);
	}	else {
		printf("multi hex -> binary test 4 passed\n");
	}

	if(!is_same(multi_hex_to_binary("AF"), "10101111")) {
		printf("multi hex -> binary test 5 failed\n");
		exit(1);
	}	else {
		printf("multi hex -> binary test 5 passed\n");
	}
	if(!is_same(binary_to_hex("0"), "0")) {
		printf("binary to hex test 1 failed\n");
		exit(1);
	}	else {
		printf("binary to hex test 1 passed\n");
	}
	if(!is_same(binary_to_hex("1"), "1")) {
		printf("binary to hex test 2 failed\n");
		exit(1);
	}	else {
		printf("binary to hex test 2 passed\n");
	}
	if(!is_same(binary_to_hex("111111111111"), "FFF")) {
		printf("binary to hex test 3 failed\n");
		exit(1);
	}	else {
		printf("binary to hex test 3 passed\n");
	}
	if(!is_same(binary_to_hex("1100101"), "65")) {
		printf("binary to hex test 4 failed\n");
		exit(1);
	}	else {
		printf("bianry to hex test 4 passed\n");
	}
	if(!is_same(binary_to_hex("000000000000"), "0")) {
		printf("binary to hex test 5 failed\n");
		exit(1);
	}	else {
		printf("binary to hex test 5 passed\n");
	}
	if(!is_same(compliment_1("0"), "1")) {
		printf("1 compliment test failed\n");
		exit(1);
	}	else {
		printf("1 compliment test passed\n");
	}
	if(!is_same(compliment_1("1"), "0")) {
		printf("1 compliment test 2 failed\n");
		exit(1);
	}	else {
		printf("1 compliment test 2 passed\n");
	}
	if(!is_same(compliment_1("01"), "10")) {
		printf("1 compliment test 3 failed\n");
		exit(1);
	}	else {
		printf("1 compliment test 3 passed\n");
	}
	if(!is_same(compliment_1("10"), "01")) {
		printf("1 compliment test 4 failed\n");
		exit(1);
	}	else {
		printf("1 compliment test 4 passed\n");
	}
	if(!is_same(compliment_1("0001"), "1110")) {
		printf("1 compliment test 5 failed\n");
		exit(1);
	}	else {
		printf("1 compliment test 5 passed\n");
	}
	if(!is_same(compliment_1("111111"), "000000")) {
		printf("1 compliment test 6 failed\n");
		exit(1);
	}	else {
		printf("1 compliment test 6 passed\n");
	}
	if(!is_same(compliment_1("000000"), "111111")) {
		printf("1 compliment test 7 failed\n");
		exit(1);
	}	else {
		printf("1 compliment test 7 passed\n");
	}

	if(!is_same(compliment_2("0"), "0")) {
		printf("2 compliment test failed\n");
		exit(1);
	}	else {
		printf("2 compliment test passed\n");
	}

	if(!is_same(compliment_2("1"), "1")) {
		printf("2 compliment test 2 failed\n");
		exit(1);
	}	else {
		printf("2 compliment test 2 passed\n");
	}

	if(!is_same(compliment_2("1000"), "1000")) {
		printf("2 compliment test 3 failed\n");
		exit(1);
	}	else {
		printf("2 compliment test 3 passed\n");
	}

	if(!is_same(compliment_2("0000"), "0000")) {
		printf("2 compliment test 4 failed\n");
		exit(1);
	}	else {
		printf("2 complimnet test 4 passed\n");
	}

	if(!is_same(compliment_2("11100101"), "00011011")) {
		printf("2 compliment test 5 failed\n");
		exit(1);
	}	else {
		printf("2 compliment test 5 passed\n");
	}
	if(!is_same(input_and_decide_type("-0b0"), "0")) {
		printf("negative bin test 1 failed\n");
		exit(1);
	}	else {
		printf("negative bin test 1 passed\n");
	}
	if(!is_same(input_and_decide_type("-0b1"), "1")) {
		printf("negative bin test 2 failed\n");
		exit(1);
	}	else {
		printf("negative bin test 2 passed\n");
	}
	if(!is_same(input_and_decide_type("-0b110"), "010")) {
		printf("negative bin test 3 failed\n");
		exit(1);
	}	else {
		printf("negative bin test 3 passed\n");
	}
	if(!is_same(input_and_decide_type("-0b001"), "111")) {
		printf("negative bin test 4 failed\n");
		exit(1);
	}	else {
		printf("negative bin test 4 passed\n");
	}
	if(!is_same(input_and_decide_type("-0b1000"), "1000")) {
		printf("negative bin test 5 failed\n");
		exit(1);
	}	else {
		printf("negative bin test 5 passsed\n");
	}
	if(!is_same(sign_or_unsign("0000", '0'), "0")) {
		printf("bit test 1 failed\n");
		exit(1);
	}	else {
		printf("bit test 1 passed\n");
	}
	if(!is_same(sign_or_unsign("0001", '0'), "1")) {
		printf("bit test 2 failed\n");
		exit(1);
	}	else {
		printf("bit test 2 passed\n");
	}
	if(!is_same(sign_or_unsign("0111", '0'), "7")) {
		printf("bit test 3 failed\n");
		exit(1);
	}	else {
		printf("bit test 3 passed\n");
	}
	if(!is_same(sign_or_unsign("1000", '0'), "8")) {
		printf("bit test 4 failed\n");
		exit(1);
	}	else {
		printf("bit test 5 passed\n");
	}
	if(!is_same(sign_or_unsign("1111", '0'), "15")) {
		printf("bit test 5 failed\n");
		exit(1);
	}	else {
		printf("bit test 5 passed\n");
	}
	if(!is_same(sign_or_unsign("0000", '1'), "0")) {
		printf("bit test 6 failed\n");
		exit(1);
	}	else {
		printf("bit test 6 passed\n");
	}
	if(!is_same(sign_or_unsign("0001",'1'), "1")) {
		printf("bit test 7 failed\n");
		exit(1);
	}	else {
		printf("bit test 7 passed\n");
	}
	if(!is_same(sign_or_unsign("0111", '1'), "7")) {
		printf("bit test 8 failed\n");
		exit(1);
	}	else {
		printf("bit test 8 passed\n");
	}
	if(!is_same(sign_or_unsign("1111", '1'), "1")) {
		printf("bit test 9 failed\n");
		exit(1);
	}	else {
		printf("bit test 9 passed\n");
	}
	if(!is_same(sign_or_unsign("1110", '1'), "2")) {
		printf("bit test 10 failed\n");
		exit(1);
	}	else {
		printf("bit test 10 passed\n");
	}
	if(!is_same(sign_or_unsign("1000", '1'), "8")) {
		printf("bit test 11 failed\n");
		exit(1);
	}	else {
		printf("bit test 11 passed\n");
	}
	

	printf("All test cases are passed\n");
}

char* multi_hex_to_binary (char *input_value) {
	
	int len = get_length (input_value);
	char *result = malloc (200);
	int j = 0;
	for (int i = 0; i < len; i++) {
		int k = 0;
		if (input_value[i] == '0' && i == 0) {
			result[i] = '0';
		}
		char *arr = single_hex_to_binary (input_value[i]);
		while (k < 4) {
			result[j] = arr[k];
			j++;
			k++;
		}

	}
	int i = 0;
	while (result[i] == '0' && result[i+1] != '\0') {
		i++;
	}
	return result+i;
}

char* single_hex_to_binary (char input) {
	
	int temp = 0;
	char *dummy = (char*) malloc (5);
	if (input >= 'A' && input <= 'F') {
		temp = input - 'A' + 10;
	}
	else if (input >= 'a' && input <= 'f') {
		temp = input - 'a' + 10;
	}
	else if (input >= '0' && input <= '9'){
		temp = input - '0';
	}
	else {
		printf ("Enter valid number format\n");
		exit(1);
	}
	int i = 3;
	while (i >= 0) {
		
		if (temp % 2 == 1) {
			dummy[i] = '1';
		}
		else {
			dummy[i] = '0';
		}
		temp /= 2;
		i--;
	}

	return dummy;
}
