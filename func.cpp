#include "func.h"
namespace commom{
	void LOG_INFO(string str){
		std::cout<<"LOG_INFO :"<<str<<std::endl;
	}
	void DEBUG_INFO(string str){
		std::cout<<"DEBUG_INFO :"<<str<<std::endl;
	}
	string GetLine( char* buffer ){
		if (buffer[strlen(buffer)-2] == '\n')
			buffer[strlen(buffer)-2] = '\0'; 
		if (buffer[strlen(buffer)-2] == '\r')
			buffer[strlen(buffer)-2] = '\0'; 
		if (buffer[strlen(buffer)-1] == '\n')	
			buffer[strlen(buffer)-1] = '\0'; 
		string bufferstr = buffer;	
		return bufferstr;	
	}	
	void Split(const char* d,const string& str, std::vector< string >& vec){
		string  delim = d; 
		vec.clear();
		size_t last = 0, index=str.find(delim,last);	
		while (index!=string::npos){
			vec.push_back(str.substr(last,index-last));	
			last=index+delim.size();index=str.find(delim,last);
		}	
		if (index-last>0)	vec.push_back(str.substr(last,index-last));
	}
	string  Unit(const string& str){
		string restr = "";
		std::vector<string> words;
		Split(" ", str, words);
		for(int jj =0; jj< words.size(); jj++){
			if(words.at(jj) == " ")continue;
			restr += words.at(jj);
		}
		return restr;
	}
	void  SplitOnce(const char* d,const string& str, std::vector< string >& vec){
		string delim = d;
		vec.clear();
		int index = str.find(delim);
		string temp ="";
		temp.append(str, 0, index);
		vec.push_back(temp);
		temp = "";
		temp.append(str, index+delim.size(),str.size()-index );
		vec.push_back(temp);
	}

	void  _Split(const char* d,const string& str, std::vector< string >& vec){
		string delim = d;
		vec.clear();
		std::map<string, int>temp;
		size_t last = 0, index=str.find(delim,last);
		while (index!=string::npos){	
			temp[str.substr(last,index-last)]++;	
			last=index+delim.size();
			index=str.find(delim,last);
		}
		if (index-last>0)	
			temp[str.substr(last,index-last)]++;	
		for(std::map<string, int>::iterator it = temp.begin(); it!= temp.end(); it++)
			vec.push_back(it->first);
	}
	void  Split(const char* d,const string& str, std::map<string, int>& vec){
		string delim = d;
		vec.clear();
		size_t last = 0,index=str.find(delim,last);
		while (index!=string::npos){	
			vec[str.substr(last,index-last)]++;	
			last=index+delim.size();
			index=str.find(delim,last);
		}	
		if (index-last>0)	vec[str.substr(last,index-last)]++;	
	}

	uint16_t StrToInt(const string& str){
		char leftstr, rightstr;	
		if(str.empty())return 0;
		int i =0;
		if(!(str[i] & 0x80)) {
			return str[i];
		}	else if ((unsigned char)str[i] <= 0xdf && i + 1 < str.size()) {
			leftstr = (str[i] >> 2) & 0x07;	
			rightstr = (str[i+1] & 0x3f) | ((str[i] & 0x03) << 6 );	
			return Combine(leftstr, rightstr);
		}	else if ((unsigned char)str[i] <= 0xef && i + 2 < str.size()) {	
			leftstr = (str[i] << 4) | ((str[i+1] >> 2) & 0x0f );	
			rightstr = ((str[i+1]<<6) & 0xc0) | (str[i+2] & 0x3f); 
			return Combine(leftstr, rightstr);	
		}else{
			return 0;
		}

	}
	bool StrToVec(const string& str,  intvector& v){
		char leftstr, rightstr;	
		if(str.empty())return false;
		v.clear();
		for( unsigned int i = 0; i <str.size(); ){
			if(!(str[i] & 0x80)) {
				v.push_back(str[i++]);
			}	else if ((unsigned char)str[i] <= 0xdf && i + 1 < str.size()) {
				leftstr = (str[i] >> 2) & 0x07;	
				rightstr = (str[i+1] & 0x3f) | ((str[i] & 0x03) << 6 );	
				v.push_back(Combine(leftstr, rightstr));	i += 2;
			}	else if ((unsigned char)str[i] <= 0xef && i + 2 < str.size()) {	
				leftstr = (str[i] << 4) | ((str[i+1] >> 2) & 0x0f );	
				rightstr = ((str[i+1]<<6) & 0xc0) | (str[i+2] & 0x3f); 
				v.push_back(Combine(leftstr, rightstr));	i += 3;	
			} else if((unsigned char)str[i] <= 0xf7 ){
				i += 4;
			} else if((unsigned char)str[i] <= 0xfb ){
				i += 5;
			} else if((unsigned char)str[i] <= 0xfd ){
				i += 6;
			}else{
				return false;
			}
		}	
		return true;
	}		
	string VecToStr(intvector& v, int i,int j ){
		string str = "";	
		if(i >= j) return str;	
		while( i != j )	{	
			if( v[i] <= 0x7f )	str += char( v[i]);	
			else if( v[i] <= 0x7ff ){
				str += char((( v[i]>>6) & 0x1f) | 0xc0);	
				str += char(( v[i] & 0x3f) | 0x80);
			} else{
				str += char((( v[i] >> 12) & 0x0f )| 0xe0);
				str += char((( v[i]>>6) & 0x3f )| 0x80 );	
				str += char(( v[i] & 0x3f) | 0x80);
			}	
			i++;
		}
		return str;
	}

	void Brackets(string& str){
		//【】[]{}
		//commom::DEBUG_INFO(str);
		string strcopy = "";
		string::size_type indexa = str.find("【");
		string::size_type indexad = 0;
		if(indexa != string::npos){
			indexad =  str.find("】");
			if((indexad != string::npos)&&(indexad > indexa)){
				strcopy.append(str,0,indexa);
				strcopy.append(str,indexad -1, str.size()-1);
			}else{
				strcopy = str;
			}
		}else{
			strcopy = str;
		}
		str = strcopy;
		strcopy = "";
		indexa = str.find("{");
		if(indexa != string::npos){
			indexad =  str.find("}");
			if((indexad != string::npos)&&(indexad > indexa)){
				strcopy.append(str,0,indexa);
				strcopy.append(str,indexad + 1, str.size()-1);
			}else{
				strcopy = str;
			}
		}else{
			strcopy = str;
		}
		str = strcopy;
		strcopy = "";
		indexa = str.find("[");
		if(indexa != string::npos){
			indexad =  str.find("]");
			if((indexad != string::npos)&&(indexad > indexa)){
				strcopy.append(str,0,indexa);
				strcopy.append(str,indexad + 1, str.size()-1);
			}else{
				strcopy = str;
			}
		}else{
			strcopy = str;
		}
		strcopy = "";
		indexa = str.find("(");
		if(indexa != string::npos){
			//commom::DEBUG_INFO("find [");
			indexad =  str.find(")");
			if((indexad != string::npos)&&(indexad > indexa)){
				//commom::DEBUG_INFO("find ]");
				strcopy.append(str,0,indexa);
				//commom::DEBUG_INFO(strcopy);
				strcopy.append(str,indexad + 1, str.size()-1);
				//commom::DEBUG_INFO(strcopy);
			}else{
				strcopy = str;
			}
		}else{
			strcopy = str;
		}
		str = strcopy;
		strcopy = "";
		indexa = str.find("（");
		if(indexa != string::npos){
			//commom::DEBUG_INFO("find [");
			indexad =  str.find("）");
			if((indexad != string::npos)&&(indexad > indexa)){
				//commom::DEBUG_INFO("find ]");
				strcopy.append(str,0,indexa);
				//commom::DEBUG_INFO(strcopy);
				strcopy.append(str,indexad + 1, str.size() - indexad );
				//commom::DEBUG_INFO(strcopy);
			}else{
				strcopy = str;
			}
		}else{
			strcopy = str;
		}
		str = strcopy;
	}

	string MapToJason(std::map<string,string>& dcit){
		//{'startDate': '2015-01-01 10:00:00',
		string str = "";
		str += "{";
		for(std::map<string,string>::iterator it = dcit.begin(); it != dcit.end(); it++){
			it++;
			if(it == dcit.end()){
				it--;
				str += "'" + it->first + "'";
				str += ":";
				str += "'" + it->second + "'";
			}else{
				it--;
				str += "'" + it->first + "'";
				str += ":";
				str += "'" + it->second + "',";
			}
		}
		str += "}";
		return str;
	}

	string GetTime(){
		string timestr = "";
		time_t timep;
		struct tm *p;
		time(&timep);
		p = localtime(&timep); //取得当地时间
		timestr += ConvertToStr(1900 + p->tm_year);
		if(1 + p->tm_mon >9){
			timestr += ConvertToStr(1 + p->tm_mon);
		}else{
			timestr += ("0" + ConvertToStr(1 + p->tm_mon));
		}
		if(p->tm_mday > 9){
			timestr += ConvertToStr(p->tm_mday);
		}else{
			timestr += ("0" +ConvertToStr(p->tm_mday));
		}		
		timestr += ConvertToStr(p->tm_hour);
		timestr += ConvertToStr(p->tm_min);
		timestr += ConvertToStr(p->tm_sec);
		return timestr;
	}
	string GetDate(){
		string timestr = "";
		time_t timep;
		struct tm *p;
		time(&timep);
		p = localtime(&timep); //取得当地时间
		timestr += ConvertToStr(1900 + p->tm_year);
		if(1 + p->tm_mon >9){
			timestr += ConvertToStr(1 + p->tm_mon);
		}else{
			timestr += ("0" + ConvertToStr(1 + p->tm_mon));
		}
		if(p->tm_mday > 9){
			timestr += ConvertToStr(p->tm_mday);
		}else{
			timestr += ("0" +ConvertToStr(p->tm_mday));
		}		
		return timestr;
	}



	char* ReadLine( char* buffer, int  size, FILE *fi ){
		memset( buffer,0,size );
		return fgets(buffer, size, fi);
	}
	int WiteLine( const char *str, FILE *fo ){
		return fputs(str,fo);
	}
	bool GetDirfile(std::vector<string>& filelist, const char* path){   
		DIR *dp;    
		struct dirent *dirp;    
		if((dp=opendir(path))==NULL){
			commom::DEBUG_INFO("open dir error");
		}
		while ((dirp=readdir(dp))!=NULL){   
			//commom::DEBUG_INFO(dirp->d_name);    	
			filelist.push_back(dirp->d_name);
		}
		closedir(dp);    
		delete(dirp);
		return true;
	}	

};
