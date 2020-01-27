#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

int get_input_data(int arr[]);
void find_interval(int arr[], int *start, int *end);
void averaging(int from[], int size);

int find_pik(int work_mass[], int size, int flag);
int comparing_sum(int mass[], int num_pik, int part_summ);
int set_output_data(int arr[], int out[], int pik0, int pik);

#define max(x, y) (x > y) ? ( x ) : ( y )
#define min(x, y) (x < y) ? ( x ) : ( y )

#define print(exp) printf(#exp) //print exp in string


int main(void){
	int arr[256];
	int out_arr[256];
	int border_up = 0, border_down = 0;
	int size;
	int pik, pik0;
		
	get_input_data(arr);
	
	find_interval(arr, &border_up, &border_down);
	
	if (border_up == 0 || border_down <= 0){
		printf("ERROR: no find 2 pik");
		scanf("end prog: PRESS KEY!");
		return -1;
	}

	printf("border up = %i\n", border_up);
	printf("border down = %i\n", border_down);
	
	
	size = border_down - border_up;
	
	int work_mass[size];
	
	for(int i = 0; i < size; ++i){	//	copy arr[border_up : border_down] in work_mass
		work_mass[i] = arr[i + border_up];
	}
	
	averaging(work_mass, size);
	
	
	pik0 = find_pik(work_mass,  size, 0) + border_up;
	pik = find_pik(work_mass,  size, 1) + border_up;
	printf("max pik0 count in %i = %i\n", pik0, arr[pik0]);
	printf("max pik count in %i = %i\n", pik, arr[pik]);
	
	for(int i = 0; i < 256; i++){
		if( i < border_up){
			out_arr[i] = arr[i];
		}else if(i >= border_up && i < border_down){
			out_arr[i] = work_mass[i - border_up];
		}else{
			out_arr[i] = arr[i];
		}
	}
	
	set_output_data(arr, out_arr, pik0, pik);
	
	scanf("end prog: PRESS KEY!");
	
	return 0;
}


int set_output_data(int arr[], int out[], int pik0, int pik){
	
	FILE* fp = fopen("out.csv", "w");
	
	if (fp == NULL){
		printf("\tERROR:\n\t-File on write not opened: Perhaps the out.csv file is open now, close it.");
		return -1;
	}
	
	fprintf(fp, "Pick_0 in %i channel\n", pik0);
	fprintf(fp, "Pick in %i channel\n", pik);
	
	for(int i = 1; i <= 256; i++){
		fprintf(fp, "%i; %i; %i\n",i, arr[i], out[i]);
	}
	
	fclose(fp);
	
	return 0;
}


void find_interval(int arr[], int *start, int *end){
	int num_limit = 4;
	int border_up = 0, border_down = 0;
	int limit = 0;
	int sign = 0;
	
	for(int i = 0; i < 255; ++i){
		if(arr[i] > arr[i + 1]){
			limit--;
		}else{
			limit++;
		}
		
		if(limit >= num_limit){
			if(sign == -1 && border_up == 0){
				border_up = i - 5;
			}
			sign = 1;
			limit = 0;
		}else if(limit <= (-1 * num_limit) ) {
			if(sign == 1 && border_down == 0){
				border_down = i - 5;
			}
			sign = -1;
			limit = 0;
		}
	}
	
	border_down = 2 * border_down - border_up;
	*start = border_up;
	*end = border_down;
	
}


int get_input_data(int arr[]){
	
	char temp_c[6];
	int c;
	
	FILE* fp = fopen("in.csv", "r");
	
	if (fp == NULL){
		printf("File on read not opened: ");
		return -1;
	}
	
	int i = 0;
	int j = 0;
	while( (c = fgetc(fp)) != EOF){
		if(isdigit(c)){
			temp_c[j++] = c;
		}else if(c = '\n'){
			arr[i++] = atoi(temp_c);
			temp_c[0] = '\0';
			temp_c[1] = '\0';
			temp_c[2] = '\0';
			temp_c[3] = '\0';
			temp_c[4] = '\0';
			temp_c[5] = '\0';
			j = 0;
		}
	}
	
	for(i; i < 256; i++){
		arr[i] = 0;
	}

	fclose(fp);
	
	return 0;
}


void clear_mas(int mas[], int n){
	for(int i = 0; i < n; ++i){
		mas[i] = 0;
	}
}


void averaging(int from[], int size){
	int to[size];
	to[0] = from[0];
	for(int i = 0; i < size - 1; ++i){
		to[i+1] = (from[i] + from[i+1]) / 2;
	}
	
	for(int i = 0; i < size - 2; ++i){
		from[i+1] = (to[i] + to[i+2]) / 2;
	}
	
	for(int i = 0; i < size - 3; ++i){
		to[i+2] = (from[i] + from[i+3]) / 2;
	}
	
	for(int i = 0; i < size - 4; ++i){
		from[i+1] = (to[i] + to[i+4]) / 2;
	}
}


int find_pik(int work_mass[], int size, int flag ){	//if flag = 0 return max_el; else return averaging max_el
	
	int max_el = 0;
	int num_max_el = 0;
	
	for(int i = 0; i < size; ++i){	//find max element
		if (work_mass[i] > max_el){
			max_el = work_mass[i];
			num_max_el = i;
		}
	}
		
	if(flag == 0){
		return num_max_el;
	}
	
	int size_part_sum;
	
	size_part_sum = min(size / 3, num_max_el);
	
	int sum_res;
	while(sum_res = comparing_sum(work_mass, num_max_el, size_part_sum)){
		if(sum_res == -1){
			num_max_el--;
		}else if(sum_res == 1){
			num_max_el++;
		}
		size_part_sum = min(size / 3, num_max_el);
	}
	return num_max_el;
}


int comparing_sum(int mass[], int num_pik, int part_summ){
	int sum_left = 0;
	int sum_right = 0;
	int max_num = mass[num_pik];
	
	for (int i = 0; i < part_summ; ++i){
		sum_left += mass[num_pik - i];
		sum_right += mass[num_pik + i];
	}
	
	if((sum_left - sum_right) > max_num){
		return -1;
	}else if((sum_right - sum_left) > max_num){
		return 1;
	}else{
		return 0;
	}
}
