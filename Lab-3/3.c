#include<stdio.h>
#include<string.h>
#include<stdlib.h>

char items[30][100][100];
char augmented_grammar[100][100], terminals[10], nonterminals[10];
int no_of_productions = 0, no_of_states = 0, no_of_items[30], no_of_terminals = 0, no_of_nonterminals = 0;

char FIRST[2][10][10];
char FOLLOW[10][10];

//Variables used only in this module.

int state_index = 0, goto_state_index = 0, closure_item_index = 0;

int check(char c) {
	int i;

	for(i = 0; i < no_of_terminals; i++)
		if(terminals[i] == c)
			return 1;

	return 0;
}

void generate_terminals() {
	int i, j;
	int index = 0;

	for(i = 0; i < no_of_productions; i++) {
		for(j = 0; augmented_grammar[i][j] != '>'; j++);
		j++;

		for(; augmented_grammar[i][j] != '\0'; j++) {
			if(augmented_grammar[i][j] < 65 || augmented_grammar[i][j] > 90) {
				if(!check(augmented_grammar[i][j])) {
					terminals[index] = augmented_grammar[i][j];
					no_of_terminals++;
					index++;
				}
			}
		}
	}

	terminals[index] = '$';
	no_of_terminals++;
	index++;
	terminals[index] = '\0';
}	

int check2(char c, int index) {
	int i;

	for(i = 0; i < index; i++)
		if(nonterminals[i] == c)
			return 1;

	return 0;
}       

void generate_nonterminals() {
	int i, index = 0;
	
	for(i = 0; i < no_of_productions; i++)
		if(!check2(augmented_grammar[i][0], index)) {
			nonterminals[index] = augmented_grammar[i][0];
			index++;
		}

	no_of_nonterminals = index;
	nonterminals[index] = '\0';
}

void initialize_items() {
	generate_terminals();
	generate_nonterminals();
	
	int i;

	for(i = 0; i < 30; i++)
		no_of_items[i] = 0;
}

void generate_item(char *s, char *t)
{
	int i;

	for(i = 0; i < 3; i++)
		t[i] = s[i];
	
	t[i] = '.';

	if(s[i] != '@')
		for(; i < strlen(s); i++)
			t[i+1] = s[i];
	
	t[i+1] = '\0';
}

int item_found(char *s) {	//Check for items in a state.
	int i;

	for(i = 0; i < closure_item_index; i++) {
		if(!strcmp(s, items[state_index][i]))	//If the strings match.
			return 1;
	}

	return 0;
}

int isterminal(char s) {
	int i;

	for(i = 0; i < no_of_terminals; i++)
		if(s == terminals[i])
			return 1;
	
	return 0;
}

void closure(char *s) {
	int i, j;

	for(i = 0; s[i] != '.'; i++); 
	
	i++;

	if(!item_found(s)) {
		strcpy(items[state_index][closure_item_index], s);
		closure_item_index++;

//		printf("%s\n", items[state_index][closure_item_index-1]);
	}

	if(s[i] == s[0] && s[i-2] == '>')	//To avoid infinite loop due to left recursion.
		return;

	if(isterminal(s[i]))
		return;
	
	else 	{	//Not a terminal
		for(j = 0; j < no_of_productions; j++) {
			char temp[100];
	
			if(augmented_grammar[j][0] == s[i]) {
				generate_item(augmented_grammar[j], temp);
				closure(temp);
			}
		}	
	}
}

int Goto1(char s, char temp[][100]) {	//Find Goto on symbol s. GOTO(goto_state_index, s)
	int i, j;
	int n = 0;
	char t, temp2[100];

	if(s == '\0') {
		return n;
	}

	for(i = 0; i < no_of_items[goto_state_index]; i++) {
		strcpy(temp2, items[goto_state_index][i]);

		for(j = 0; temp2[j] != '.'; j++);

		if(temp2[j+1] == '\0')
			continue;

		if(temp2[j+1] == s) {
			t = temp2[j];
			temp2[j] = temp2[j+1];
			temp2[j+1] = t;

			strcpy(temp[n], temp2);
			n++;
		}
	}

	return n;
}

int state_found(char *s) {	//Checks for existance of same state.
	int i;
	
	for(i = 0; i < state_index; i++) {
		if(!strcmp(s, items[i][0]))	//Compare with the first item of each state.
			return 1;
	}

	return 0;
}

int transition_item_found(char * t_items, char s, int t_index) {
	int i;

	for(i = 0; i < t_index; i++)
		if(s == t_items[i])
			return 1;
	
	return 0;
}

void compute_closure_goto() {
	char temp[100][100], transition_items[100];
	int i, no_of_goto_items,j, transition_index = 0;
	//add . to the grammer
	generate_item(augmented_grammar[0], temp[0]);
//it will compute closure of the variable after .
	closure(temp[0]);

	no_of_items[state_index] = closure_item_index;
	closure_item_index = 0;

	state_index++;
	//state_index is 1 now.

	while(goto_state_index < 30) {
		transition_index = 0;
		transition_items[transition_index] = '\0';

		for(i = 0; i < no_of_items[goto_state_index]; i++) {
			for(j = 0; items[goto_state_index][i][j] != '.'; j++);
			j++;

			if(!transition_item_found(transition_items, items[goto_state_index][i][j], transition_index)) {
				transition_items[transition_index] = items[goto_state_index][i][j];
				transition_index++;
			}
		}

		transition_items[transition_index] = '\0';

		for(i = 0; i < transition_index; i++) {
			int add_flag = 0;

			no_of_goto_items = Goto1(transition_items[i], temp);
	
			for(j = 0; j < no_of_goto_items; j++) {
				if(!state_found(temp[j])) {
					add_flag = 1;
					closure(temp[j]);
				}
				else
					break;
			}
			if(add_flag) {
				no_of_items[state_index] = closure_item_index;
				closure_item_index = 0;
				state_index++;
			}
		}

		goto_state_index++;
	}
	
	no_of_states = state_index;
}

void print() {
	int i, j;

	printf("\nNumber of states = %d.\n", no_of_states);

	for(i = 0; i < no_of_states; i++) {
		printf("\n\nItems in State %d : \n\n", i);

		for(j = 0; j < no_of_items[i]; j++)
			printf("\t%s\n", items[i][j]);
	}
}
//End of Parsing Table.
//Parsing Table.
struct Parsing_Table {	//Structure to represent the Parsing Table.	
	char ACTION[30][100][100];
	int GOTO[30][100];
} table;

void initialize_table() {  //Initialize all entries to indicate Error.
	int i, j;

	for(i = 0; i < no_of_states; i++) {
		for(j = 0; j < no_of_terminals; j++)
			strcpy(table.ACTION[i][j], "e");

		for(j = 0; j < no_of_nonterminals; j++)
			table.GOTO[i][j] = -1;
	}
}

void print_table() {
	int i, j;

	printf("\nThe Parsing Table for the given grammar is...\n\n");

	printf("%10s   ", "");
	
	for(i = 0; i < no_of_terminals; i++)
		printf("%10c", terminals[i]);

	printf(" | ");
	
	for(i = 1; i < no_of_nonterminals; i++)
		printf("%10c", nonterminals[i]);

	printf("\n\n");

	for(i = 0; i < no_of_states; i++) {
		printf("%10d | ", i);

		for(j = 0; j < no_of_terminals; j++) {
			if(!strcmp(table.ACTION[i][j], "e"))
				printf("%10s", ".");
			else
				printf("%10s", table.ACTION[i][j]);
		}

		printf(" | ");

		for(j = 1; j < no_of_nonterminals; j++) {
			if(table.GOTO[i][j] == -1)
				printf("%10s", ".");
			else
				printf("%10d", table.GOTO[i][j]);
		}

		printf("\n");
	}
}

void Goto(int i, int item, char *temp) {	//Computes goto for 'item'th item of 'i'th state.
	char t;

	strcpy(temp, items[i][item]);

	for(i = 0; temp[i] != '\0'; i++)
		if(temp[i] == '.') {
			t = temp[i];
			temp[i] = temp[i+1];
			temp[i+1] = t;
			break;
		}
}

int get_state(char *t, int state) {	//Returns the state of a given item.
	int i, j;

	for(i = state; i < (no_of_states + state); i++) {	//Start searching from current state and then wrap around.
		for(j = 0; j < no_of_items[i % no_of_states]; j++) {
			if(!strcmp(t, items[i % no_of_states][j]))
				return i % no_of_states;
		}
	}
  return 0;

	printf("No match for string! (%s)\n", t);
}

int get_pos(int flag, char symbol) {	//Returns index of a terminal or a non-terminal from the corresponding arrays.
	int i;

	if(flag == 0)
		for(i = 0; i < no_of_terminals; i++) {
			if(terminals[i] == symbol) 
				return i;
		}
	else
		for(i = 0; i < no_of_nonterminals; i++) {
			if(nonterminals[i] == symbol) 
				return i;
		}				

	if(flag == 0)
		printf("Terminal not found in get_pos! (%c)\n", symbol);
	else
		printf("Non-terminal not found in get_pos! (%c)\n", symbol);
  
  return 0;
}

int get_production_no(char * item) {	//Given an item, it returns the production number of the equivalent production.
	int i, j;
	
	char production[20];

	for(i = 0, j = 0; item[i] != '\0'; i++)
		if(item[i] != '.') {
			production[j] = item[i];
			j++;
		}
	
	if(j == 3) {		//If it's an epsilon production, the production won't have a body.
		production[j] = '@';
		j++;
	}
	
	production[j] = '\0';

	for(i = 0; i < no_of_productions; i++) {
		if(!strcmp(production, augmented_grammar[i]))
			return i;
  
	}

	printf("Production not found! (%s)\n", production);
  return 0;
}

void compute_action() {
	int i, item, j;
	char temp[100], symbol;
	
	for(i = 0; i < no_of_states; i++) {
		for(item = 0; item < no_of_items[i]; item++) {
			char *s = strchr(items[i][item], '.');	//Returns a substring starting with '.'
			
			if(!s) {	//In case of error.
				printf("Item not found! State = %d, Item = %d\n", i, item);
				exit(-1);
			}

			if(strlen(s) > 1) {	//dot is not at end of string. SHIFT ACTION!!
				if(isterminal(s[1])) {		//For terminals. Rule 1.
					if(strcmp(table.ACTION[i][get_pos(0,s[1])], "e")) {		//Multiple entries conflict.
						printf("\n\nConflict(1): Multiple entries found for (%d, %c)\n", i, s[1]);
						printf("\nGrammar is not in LR(0)!\n");
						exit(-1);
					}

					char state[3];
	
					Goto(i, item, temp);	//Store item in temp.
					j = get_state(temp, i);

					sprintf(state, "%d", j);
					strcpy(temp, "S:");
					strcat(temp, state);

					strcpy(table.ACTION[i][get_pos(0, s[1])], temp);
				}
				
				else {		//For non-terminals. Rule 4.
					
					Goto(i, item, temp);	//Store item in temp.
					j = get_state(temp, i);

					if(table.GOTO[i][get_pos(1, s[1])] == -1)	//To avoid multiple entries.
						table.GOTO[i][get_pos(1, s[1])] = j;
				}
			}

			else {	//dot is at end of string. Rule 2. REDUCE ACTION!!	
				char f[10], production_no[3];
				int k, n;
				n = get_production_no(items[i][item]);		//Get production number from Augmented Grammar.

				sprintf(production_no, "%d", n);
				strcpy(temp, "R:");
				strcat(temp, production_no);
				
				strcpy(f, FOLLOW[get_pos(1, items[i][item][0])]);	//Get follow of production head.
				for(k = 0; f[k] != '\0'; k++) {
					if(strcmp(table.ACTION[i][get_pos(0, f[k])], "e")) {		//Multiple entries conflict.
						printf("\n\nConflict(3): Multiple entries found for (%d, %c)\n", i, f[k]);
						printf("\nGrammar is not in LR(0)!\n");
						exit(-1);
					}

					strcpy(table.ACTION[i][get_pos(0, f[k])], temp);
				}
			}
		}
	}

	strcpy(table.ACTION[1][get_pos(0, '$')], "acc");	//Accept-entry for item [S'->S.]
}

void create_parsing_table() {
	initialize_table();

	compute_action();

	print_table();
}

//End of Parsing Table.

int main() {
	char str[100];

	printf("Enter number of productions:");
	scanf("%d", &no_of_productions);

	printf("Enter the productions...\n");
	
	int i;
	for(i = 1; i <= no_of_productions; i++)
		scanf("%s", augmented_grammar[i]);

	printf("\n\nAugmented Grammar is...\n\n");

	strcpy(augmented_grammar[0], "Z->");
	str[0] = augmented_grammar[1][0];
	str[1] = '\0';
	strcat(augmented_grammar[0], str);

	no_of_productions++;

	for(i = 0; i < no_of_productions; i++)
		printf("%s\n", augmented_grammar[i]);

	initialize_items();

	compute_closure_goto();

	print();

  create_parsing_table();
  return 0;
}
