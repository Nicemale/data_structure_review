// algorithmic process:
/*
	Target:
		reduce recall times of target string, when target string mismatch before, we need to move current char pointer of target string  to the first character and right shift source string to continuely match, but now we wanna find a way out to reduce target stirng recall times or even no need for one time recall can complete the match.
	Generalization:
		we need two steps to finish KMP match algorithm, 1: compute out the next arrary that next[J] recored how many char from the beginning of current target string are same with the chars front of current string[J] of  current index J; 2: using next arrary in step 1 to reduce recall times, if we mismatch at index 3, then we know that the s[1]s[2] t[1]t[2] are matched, now let's see next[3]=2, which means there two chars in front of t[3] are same with t[0]t[1], that's saying t[1]t[2] == t[0]t[1] == s[1]s[2], okay, now we can alignment s[1]s[2] t[0]t[1], and match source string with i = 3(startindex + next[3]) target string index next[3].

*/
#include <stdio.h>
#define NEXT_SIZE 100
int next[NEXT_SIZE] = {-2};
int str_len(char * str){
	int t_len = 0;
	while(str[t_len] != '\0'){
		t_len++;
	}
//	printf("t_len = %d\n",t_len);
	return t_len;
}
void Next(char t[]){
	next[0] = -1;
	int j = 0;
	int k = -1;
	int t_len = str_len(t);
	while(j<t_len-1){
		if(k == -1 || t[j] == t[k]){
			k++;
			j++;
			next[j] = k;
		}else{
			k = next[k]; // k意味着t[j]前k个元素与当前串前k个元素相同，因此，此处将k回溯到第k+1个元素处,下次再与t[j]进行比较
		}
	}
}
int Kmp(char *s, char *t){
	int ret = 0;
	Next(t);
	int s_len = str_len(s);
	int t_len = str_len(t);
	//printf("s_len:%d,t_len:%d",s_len,t_len);
	int i = 0,j = 0;
	while(i < s_len && j < t_len){
		if(j==-1 || s[i] == t[j]){ //j==-1时，表示t[0]与s[i]不匹配，此时s向右移动一位继续下一位进行匹配
			i ++;
			j ++;
		}else{
			// right shift target string
			j = next[j];
		}
	}
	if(j >= t_len){
		//子串匹配完成，正常情况下只会出现 t== t_len
		ret = i - t_len;
	}else{
		ret = -1; //未匹配到结果
	}
	//printf("j的值为:%d,i的值：%d,s_len的值%d",j,i,s_len);
	return ret;
}
int main(int argc,char *argv[]){
	char *s = NULL;
	char *t = NULL;	
	if(argc < 3){
		printf("参数个数错误!\n");
		return 0;
	}else{
		s = argv[1];
		t = argv[2];
	}
	int start_index = Kmp(s,t);
	if(start_index == -1){
		printf("匹配失败!\n");
	}else{
		printf("匹配成功，起始索引为：%d",start_index);
	}
}

