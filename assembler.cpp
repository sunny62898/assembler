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
	fpOp = fopen("opcode.txt","r");   //�}��
	int opSize = 1;
	char ch;
	
	/*��opcode���X�� */
	while(fscanf(fpOp,"%c",&ch) != -1){  
		if(ch == '\n'){
			opSize++;
		}
	
	} 
	fclose(fpOp);  //���� 
	/*�⧹opcodeSize*/
	struct opcode opcode[opSize];
	
	/*read opcode.txt���e*/
	//FILE *fpOp;
	fpOp = fopen("opcode.txt","r");   //�}��
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
	fclose(fpOp);  //���� 
	/*end of read opcode.txt���e*/
	
	
	FILE *fpSource;
	fpSource = fopen("source.txt","r");   //�}��
	int SSize = 1;
	
	/*�p��source.txt���j�p*/
	while(fscanf(fpSource,"%c",&ch) != -1){  
		if(ch == '\n'){
			SSize++;
		}
	
	} 
	fclose(fpSource);  //���� 
	/*�⧹SourceSize*/
	struct source source[SSize];
	
	fpSource = fopen("source.txt","r");   //�}��
	index = 0;
	/*read source.txt���e*/
	while(fscanf(fpSource,"%c",&ch) != -1){
		printf("%d , %c\n",index,ch);
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
			source[index].type[i] = ch;
			i++;
			fscanf(fpSource,"%c",&ch);
		}
		//printf("\n",ch);
		fscanf(fpSource,"%c",&ch);
		i = 0;
		while(ch != '\n'){ //content
			//printf("%c",ch);
			source[index].content[i] = ch;
			i++;
			if(fscanf(fpSource,"%c",&ch) == -1){
				break;
			}
		}
		printf("%s\n",source[index].type);
		index++;
			
	}
	fclose(fpSource);  //���� 
	
	printf("%d\n",SSize);
	
	system("PAUSE");
	return 0;
} 