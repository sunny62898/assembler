#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct opcode{
	char operate[16] = {};
	char operateCode[16] = {};
};

struct source{
	int location = 0;
	char name [16] = {};
	char type [16] = {};
	char content [16] = {};
	char objectCode[6] = {};
};

struct symbol{
	int address = 0;
	char label[16] = {};
};

int main(){
	
	//pass one
	/*read file begain*/
	FILE *fpOp;
	fpOp = fopen("opcode.txt","r");   //開檔
	int opSize = 1;
	char ch;
	int check = 0;
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
		
		/*test " "*/
		check = 0;
		while(source[index].name[check] != '\0'){
			if(source[index].name[check] == ' '){
				source[index].name[check] = '\0';
			}
			check++;
		}
		check = 0;
		while(source[index].type[check] != '\0'){
			if(source[index].type[check] == ' '){
				source[index].type[check] = '\0';
			}
			check++;
		}
		check = 0;
		while(source[index].content[check] != '\0'){
			if(source[index].content[check] == ' '){
				source[index].content[check] = '\0';
			}
			check++;
		}
		
		index++;
			
	}
	fclose(fpSource);  //關檔
	/*end of read source.txt內容*/
	
	
	
	/*算location*/
	//START
	int run = 0;
	while(source[0].content[run] != '\0'){
		source[0].location = source[0].location*16 + (source[0].content[run] - '0');
		run++;
	}
	
	//FIRST
	source[1].location = source[0].location;
	//other
	int count = 0;
	for(int i = 2;i < SSize-1;i++){
		if(strcmp(source[i-1].type,"BYTE")  == 0){
			if(source[i-1].content[0] == 'X'){
				source[i].location = source[i-1].location+1;
			}
			else{
				run = 2;
				count = 0;
				while(source[i-1].content[run] != '\''){
					count++;
					run++;
				}
				source[i].location = source[i-1].location + count;
			}
		} 
		else if(strcmp(source[i-1].type,"RSUB") == 0){
			source[i].location = source[i-1].location+3;
		}
		else if(strcmp(source[i-1].type,"RESB") == 0){
			run = 0;
			while(source[i-1].content[run] != '\0'){
				source[i].location = source[i].location*10 + (source[i-1].content[run] - '0');
				run++;
			}
			//printf("4096 = %d\n",source[i].location);
			source[i].location = source[i].location + source[i-1].location;
		}
		else{
			source[i].location = source[i-1].location + 3;
		}
		
	}
	
	/*write in intermediate txt*/
	FILE *intermediate;
	intermediate = fopen("intermediate.txt","w");
	fprintf(intermediate,"Loc\t\tSource statment\n\n");
	for(int i = 0;i < SSize;i++){
		if(strcmp(source[i].type,"END") == 0){
			fprintf(intermediate," \t \t%s\t%s\n",source[i].type,source[i].content);
		}
		else if(source[i].name[0] == '\0' && source[i].content[0] != '\0'){
			fprintf(intermediate,"%X\t \t%s\t%s\n",source[i].location,source[i].type,source[i].content);
		}
		else if(source[i].name[0] != '\0' && source[i].content[0] == '\0'){
			fprintf(intermediate,"%X\t%s\t%s\t	\n",source[i].location,source[i].name,source[i].type);
		}
		else if(source[i].name[0] == '\0' && source[i].content[0] == '\0'){
			fprintf(intermediate,"%X\t \t%s\t	\n",source[i].location,source[i].type);
		}
		else{
			fprintf(intermediate,"%X\t%s\t%s\t%s\n",source[i].location,source[i].name,source[i].type,source[i].content);
		}
	}
	fclose(intermediate);  //關檔
	/*end of write in intermediate.txt*/
	
	/*write in symbol.txt*/
	//count symbol number
	int symbolnum = 0;
	for(int i = 0;i < SSize;i++){
		if(source[i].name[0] != '\0'){
			symbolnum++;
		}
	}
	
	//make symbol table
	int top = 0;
	struct symbol symbol[symbolnum];
	for(int i = 0;i < SSize;i++){
		if(source[i].name[0] != '\0' && strcmp(source[i].name,"COPY") != 0){
			strcpy(symbol[top].label,source[i].name);
			symbol[top].address = source[i].location;
			top++;
		}
	}
	
	/*output symbol test*/
	FILE *sym;
	sym = fopen("SymbolTabel.txt","w");
	fprintf(sym,"Label name\tAddress\n");
	for(int i = 0;i < top;i++){
		fprintf(sym,"%s\t\t%X\n",symbol[i].label,symbol[i].address);
	}
	fclose(sym);  //關檔
	/*end of write in symbol.txt*/
	
	//end of pass one
	
	
	//pass two
	int testX = 0;
	int other = 0;
	char cal[4] = {};
	
	for(int i = 0;i < SSize;i++){  //run every source
		testX = 0;
		other = 0;
		//opCode
		for(int j = 0;j < opSize;j++){  
			if(strcmp(source[i].type,opcode[j].operate) == 0){
				source[i].objectCode[0] = opcode[j].operateCode[0];
				source[i].objectCode[1] = opcode[j].operateCode[1];
				
				break;
			}
		}
		
		//location
		/*find ",X"*/
		run = 0;
		while(source[i].content[run] != '\0'){
			if(source[i].content[run] == ','){
				if(source[i].content[run+1] == 'X'){
					testX = 1;
					break;
				}
			}
			run++;
		}
		
		if(testX == 1){  //有 ",X" 
			
		}
		else if(testX == 0){  //沒有 ",X" 
			for(int j = 0;j < top;j++){
				if(strcmp(source[i].content,symbol[j].label) == 0){
					
					sprintf(cal,"%X",symbol[j].address);
					printf("%s\n",cal);
					break;
					 
				}
				
			}
		}
		
		
	}
	
	system("PAUSE");
	return 0;
} 
