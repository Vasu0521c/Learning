#include<stdio.h>
#include<stdlib.h>

typedef struct directory directory;

struct directory{

	char name[100];
	char *data;
	directory *root_dir;
	directory *next_dir;
	directory *child_dir;
	directory *parent_dir;
	int is_file;
};

directory* create_directory() {

	directory *created_directory = malloc(sizeof(directory));
	created_directory -> root_dir   = NULL;
	created_directory -> next_dir   = NULL;
	created_directory -> child_dir  = NULL;
	created_directory -> parent_dir = NULL;
	created_directory -> is_file    = 0;
}

void list_directory_contents(directory *dir);
void print_current_directory(directory *dir);
void who_am_i();
void make_directory(directory *dir, char *str);
void remove_file(directory *dir, char *str);
void touch(directory *dir, char *str);
void touch_with_data(directory *dir, char *str, char *input);
void move_or_rename(directory *dir, char *str_a, char *str_b);
void clear();
directory* change_directory(directory *dir, char *str);
void copy();
void cat(directory *dir, char *file_name);

int compare(char *str_a,char *str_b);

void str_copy(char *str_a, char *str_b) {
	
	int i = 0;
	while(str_b[i] != '\0') {
		str_a[i] = str_b[i];
		i++;
	}
}

int str_contains(char *str, char target) {

	int i = 0;
	while(str[i] != '\0') {
		if(str[i] == target)
			return 1;
		i++;
	}
	return 0;
}

void cat(directory *dir, char *filename) {

	directory *temp = dir -> child_dir;
	if(temp == NULL) {
		printf("No file named %s is here.",filename);
		return;
	}
	while(compare(temp -> name, filename) != 1) {
		if(temp -> next_dir != NULL)
			temp = temp -> next_dir;
		else {
			printf("no file named %s exist", filename);
			return;
		}
	}
	printf("%s", temp -> data);
	return;
}

int get_length(char *str) {

	if(str == NULL)
		return 0;
	int i = 0;
	while(str[i] != '\0')
		i++;
	return i;
}

int compare(char* str_a, char* str_b) {

	int len_a = get_length(str_a);
	if(len_a != get_length(str_b))
		return 0;
	int i = 0;
	while(i < len_a) {
		if(str_a[i] != str_b[i]) 
			return 0;
		i++;
	}
	return 1;
}

directory* change_directory(directory *dir, char *str) {

	if(compare(str, "/") == 1) {
		while(dir -> parent_dir != NULL) {
			dir = dir -> parent_dir;
			return dir;
		}
	}
	directory *temp = dir -> child_dir;
	while(compare(temp -> name, str) != 1) {
		if(temp -> next_dir != NULL) 
			temp = temp -> next_dir;
		else {
			printf("No directory named %s found.",str);
			return dir;
		}
	}
	dir = temp;
	return dir;
}

void list_directory_contents(directory *dir) {

	directory *temp = dir -> child_dir;
	if(temp == NULL) {
		printf("directory is Empty.\n");
		return;
	}
	printf("Name    |      Type\n");
	printf("--------------------\n");
	char c = 'D';
	while((temp -> next_dir) != NULL) {
		if(temp -> is_file == 1) {
			c = 'F';
		}
		printf("%-8s|%2c\n",temp -> name, c);
		temp = temp -> next_dir;
	}
	printf("%-8s|%2c\n",temp -> name, c);
}

void print_current_directory(directory *dir) {
	
	printf("\n%s\n", dir -> name);
}

void whoami() {
	
	printf("root\n");
}

void make_directory(directory *dir, char *Name) {

	if(dir -> child_dir == NULL) {
		dir -> child_dir               = create_directory();
		dir -> child_dir -> parent_dir = dir;
		str_copy(dir -> child_dir -> name, Name);
		return;
	}
	directory *temp = dir -> child_dir;
	while(temp -> next_dir != NULL) {
		temp = temp -> next_dir;
	}
	directory *created_dir    = create_directory();
	str_copy(created_dir -> name, Name);
	created_dir -> parent_dir = dir;
	temp -> next_dir          = created_dir;
	return;
}

void remove_file(directory *dir, char *str) {

	directory *temp = dir -> child_dir;
	directory *prev = temp;
	while(compare(temp -> name, str) != 1) {
		if(temp != NULL) {
			prev = temp;
			temp = temp -> next_dir;
		}
		else {
			printf("No filed named %s exists\n",str);
			return;
		}
	}
	if(temp -> next_dir != NULL)
		prev -> next_dir = temp -> next_dir;
	else
		prev -> next_dir = NULL;
	if(temp == dir -> child_dir) {
		if(temp -> next_dir != NULL)
			dir -> child_dir = temp -> next_dir;
		else
			dir -> child_dir = NULL;
	}
	free(temp);
	return;
}

void touch(directory *dir, char *str) {
	
	if(dir -> child_dir == NULL) {
		dir -> child_dir               = create_directory();
		dir -> child_dir -> parent_dir = dir;
		str_copy(dir -> child_dir -> name, str);
		return;
	}
	directory *temp = dir -> child_dir;
	while(temp -> next_dir != NULL)
		temp = temp -> next_dir;
	directory *created_dir    = create_directory();
	str_copy(created_dir -> name, str);
	created_dir -> parent_dir = dir;
	temp -> next_dir          = created_dir;
	return;
}

void touch_with_data(directory *dir, char *str, char *input) {
	
	if(dir -> child_dir == NULL) {
		dir -> child_dir               = create_directory();
		dir -> child_dir -> parent_dir = dir;
		dir -> child_dir -> data       = malloc(sizeof(input));
		dir -> child_dir -> is_file    = 1;
		str_copy(dir -> child_dir -> name, str);
		str_copy(dir -> child_dir -> data, input);
		return;
	}
	directory *temp = dir -> child_dir;
	while(temp -> next_dir != NULL)
		temp = temp -> next_dir;
	directory *created_dir    = create_directory();
	created_dir -> data       = malloc(sizeof(input));
	str_copy(created_dir -> data, input);
	str_copy(created_dir -> name, str);
	created_dir -> is_file    = 1;
	created_dir -> parent_dir = dir;
	temp -> next_dir          = created_dir;
	return;
}

void move_or_rename(directory *dir, char *str_a, char *str_b) {

	directory *c_name = dir;
	directory *temp   = dir -> child_dir;
	directory *prev   = temp;
	while(compare(temp -> name, str_a) != 1) {
		if(temp != NULL) {
			prev = temp;
			temp = temp -> next_dir;
		}
		else
			return;
	}
	str_copy(temp -> name, str_b);
}

void test();

int main() {
	
	directory *dir = create_directory();
	str_copy(dir -> name, "root");
	char input[500];
	char arguments[100][100];
	while(1) {
		printf("%s$ ",dir -> name);
		fgets(input, sizeof(input), stdin);
		int i = 0;
		int j = 0;
		int k = 0;
		while(input[i] != '\n' && input[i] != '\0') {
			while(input[i] != ' ' && input[i] != '\0' && input[i] != '\n') {
				arguments[j][k] = input[i];
				i++;
				k++;
			}
			arguments[j][k] = '\0';
			k = 0;
			i++;
			j++;
		}
		i = 0;
		if(compare(arguments[i], "mkdir")) {
			while(i < j - 1) {
				++i;
				make_directory(dir, arguments[i]);
			}
		}
		else if(compare(arguments[i], "ls")) {
			list_directory_contents(dir);
		}
		else if(compare(arguments[i], "pwd"))
			print_current_directory(dir);
		else if(compare(arguments[i], "whoami"))
			whoami();
		else if(compare(arguments[i], "touch")) {
			if(str_contains(arguments[i + 2], '"') == 1) {
				touch_with_data(dir, arguments[i + 1], arguments[i + 2]);
				continue;
			}
			while(i < j - 1) {
				i++;
				touch(dir, arguments[i]);
			}
		}
		else if(compare(arguments[i], "rm")) {
			while(i < j - 1) {
				i++;
				remove_file(dir, arguments[i]);
			}
		}
		else if(compare(arguments[i], "mv"))
			move_or_rename(dir, arguments[1], arguments[2]);
		else if(compare(arguments[i], "cd")) {
			while(i < j - 1) {
				i++;
				dir = change_directory(dir, arguments[i]);
			}
		}
		else if(compare(arguments[i], "cat"))
			cat(dir, arguments[i + 1]);
		else if(compare(arguments[i], "exit"))
			exit(1);
		else
			printf("enter valid command\n");


	}
	test();
	return 0;
}

void test() {

	directory *dir = create_directory();
	make_directory(dir, "Dummy_folder");
	if(compare(dir -> child_dir -> name, "Dummy_folder") != 1) {
		printf("Make directory test 1 failed\n");
		exit(1);
	}	else {
		printf("Make directory test 1 passed\n");
	}
	make_directory(dir, "Dummy_folder_b");
	if(compare(dir -> child_dir -> next_dir -> name, "Dummy_folder_b") != 1) {
		printf("Make directory test 2 failed\n");
		exit(1);
	}	else {
		printf("Make directory test 2 passed\n");
	}
	remove_file(dir, "Dummy_folder_b");
	if(dir -> child_dir -> next_dir != NULL) {
		printf("remove test 1 failed\n");
		exit(1);
	}	else {
		printf("remove test 1 passed\n");
	}
	remove_file(dir, "Dummy_folder");
	if(dir -> child_dir != NULL) {
		printf("remove test 2 failed\n");
		exit(1);
	}	else {
		printf("remove test 2 passed\n");
	}
	touch(dir, "Anything_file");
	if(dir -> child_dir == NULL) {
		printf("touch test 1 failed\n");
		exit(1);
	}	else {
		printf("touch test 1 passed\n");
	}
	move_or_rename(dir, "Anything_file", "Renamed_file");
	if(compare(dir -> child_dir -> name, "Renamed_file") != 1) {
		printf("Rename test 1 failed\n");
		exit(1);
	}	else {
		printf("Renme test 1 passed\n");
	}
}
