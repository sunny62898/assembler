#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct opcode{
	char operate[16] = {};
	char operateCode[16] = {};
};

struct source{
	int location;
	char name [16] = {};
	char type [16] = {};
	char content [16] = {};
};

int main(){
	
	/*read file begain*/
	FILE *fpOp;
	fpOp = fopen("opcode.txt","r");   //開檔
	int opSize = 1;
	char ch;
	
	/*算opcode有幾個 */
	while(fscanf(fpOp,"%c",&ch) != -1){  
		if(ch == '\n'){
			opSize++;
		}
	
	} 
	fclose(fpOp);  //關檔 
	/*算完opcodeSize*/
	struct opcode opcode[opSize];
	
	/*read opcode.txt內容*/
	//FILE *fpOp;
	fpOp = fopen("opcode.txt","r");   //開檔
	int index = 0;
	while(fscanf(fpOp,"%c",&ch) != -1){
		int i = 0;
		if((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z')){  //operation
			opcode[index].operate[i] = ch;
			i++;
			fscanf(fpOp,"%c",&ch);
			while(ch != ' '){
				opcode[index].operate[i] = ch;
				i++;
				fscanf(fpOp,"%c",&ch);
			}
		}
		fscanf(fpOp,"%c",&ch);
		i = 0;
		while(ch != '\n'){    //opcode
			opcode[index].operateCode[i] = ch;
			if(fscanf(fpOp,"%c",&ch) == -1){
				break;
			}
			i++;
		}	
		
		
		if(ch == '\n'){
			index++;
		}
	}
	fclose(fpOp);  //關檔 
	/*end of read opcode.txt內容*/
	
	
	FILE *fpSource;
	fpSource = fopen("source.txt","r");   //開檔
	int SSize = 1;
	
	/*計算source.txt的大小*/
	while(fscanf(fpSource,"%c",&ch) != -1){  
		if(ch == '\n'){
			SSize++;
		}
	
	} 
	fclose(fpSource);  //關檔 
	/*算完SourceSize*/
	struct source source[SSize];
	
	fpSource = fopen("source.txt","r");   //開檔
	index = 0;
	/*read source.txt內容*/
	while(fscanf(fpSource,"%c",&ch) != -1){
		int i = 0;
		while(ch != '\t'){ //name 
			//printf("%c",ch);
			source[index].name[i] = ch;
			i++;
			fscanf(fpSource,"%c",&ch);
		}
		fscanf(fpSource,"%c",&ch);
		i = 0;
		while(ch != '\t'){ //type
			//printf("%c",ch);
			if(ch == '\n'){
				break;
			}
			source[index].type[i] = ch;
			i++;
			fscanf(fpSource,"%c",&ch);
		}
		//printf("\n",ch);
		if(ch != '\n'){
			fscanf(fpSource,"%c",&ch);
		}
		
		i = 0;
		while(ch != '\n'){ //content
			//printf("%c",ch);
			source[index].content[i] = ch;
			i++;
			if(fscanf(fpSource,"%c",&ch) == -1){
				break;
			}
		}
		
		/*test output*/
		if(source[index].name[0] == '\0' && source[index].content[0] != '\0'){
			printf("	%s %s\n",source[index].type,source[index].content);
		}
		else if(source[index].name[0] != '\0' && source[index].content[0] == '\0'){
			printf("%s %s	\n",source[index].name,source[index].type);
		}
		else if(source[index].name[0] == '\0' && source[index].content[0] == '\0'){
			printf("	%s	\n",source[index].type);
		}
		else{
			printf("%s %s %s\n",source[index].name,source[index].type,source[index].content);
		}
		/*test output end*/
		
		index++;
			
	}
	fclose(fpSource);  //關檔
	/*end of read source.txt內容*/
	
	
	system("PAUSE");
	return 0;
} 
