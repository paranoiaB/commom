#ifndef _FUNC_H
#define _FUNC_H
#include <stdio.h>
#include <iostream>
#include <string>
#include "string.h"
#include <stdlib.h>
#include <stdint.h>
#include <sys/types.h>    
#include <sys/stat.h>
#include <vector>
#include <sstream>
#include <map>
#include <dirent.h>  
#include <time.h>
#define SHORT_LENTH 250
#define MAX_LENTH 50000
typedef FILE* _FILE;
typedef std::string string;
typedef struct{ string word; float d;}wdlen;
typedef  std::vector<uint16_t>  intvector;
namespace commom{
	//日志类
	void LOG_INFO(string str);
	void DEBUG_INFO(string str);

	//字符串处理
	string GetLine( char* buffer );
	string  Unit(const string& str);
	void Split(const char* d,const string& str, std::vector< string >& vec);
	void Split(const char* d,const string& str, std::map<string, int>& vec);
	void _Split(const char* d,const string& str, std::vector< string >& vec);
	void SplitOnce(const char* d,const string& str, std::vector< string >& vec);			
	inline uint16_t Combine(char high, char low){	return (((uint16_t(high) & 0x00ff ) << 8) | (uint16_t(low) & 0x00ff));	}		
	bool StrToVec(const string& str,  intvector& v);
	uint16_t  StrToInt(const string& str);
	string  VecToStr(intvector& v, int i,int j );
	string MapToJason(std::map<string,string>& dcit);
	//去括号里内容
	void Brackets(string& str);
	//文件处理
	char* ReadLine( char* buffer, int  size, FILE *fi );
	int WiteLine( const char *str, FILE *fo );
	bool GetDirfile(std::vector<string>& filelist, const char* path);
	//时间处理
	string GetTime();
	string GetDate();

	//常用模版
	template <class T> int MaxArray(T* prob, int n){
		if((n < 1 )||(prob == NULL))return -1;
		T temp = prob[0];	int index =0;
		for(int i =0; i< n; i++){
			if(temp < prob[i] ){
				temp = prob[i]; 	index = i;
			}
		}
		return index;
	}
	template <class T> int MinArray(T* prob, int n){
		if((n < 1 )||(prob == NULL))return -1;
		T temp = prob[0];	int index =0;
		for(int i =0; i< n; i++){
			if(temp > prob[i] ){
				temp = prob[i]; 	index = i;
			}
		}
		return index;
	}
	template <class T> string ConvertToStr(T value) {
		std::stringstream ss;	ss << value;	return ss.str();
	}
	static bool SortByDistance(const wdlen& x, const wdlen& y){
		return x.d > y.d;
	}
	static bool SortBySecondGreater(const std::pair<string, float>& x, 
		const std::pair<string, float>& y ){
			return x.second > y.second;
	}
	static bool SortBySecondLess(const std::pair<string, float>& x, 
		const std::pair<string, float>& y ){
			return x.second < y.second;
	}
	/*
	class Func{
	public://字符串处理
		string GetLine( char* buffer );
		string  Unit(const string& str);
		void Split(const char* d,const string& str, std::vector< string >& vec);
		void Split(const char* d,const string& str, std::map<string, int>& vec);
		void _Split(const char* d,const string& str, std::vector< string >& vec);
		void SplitOnce(const char* d,const string& str, std::vector< string >& vec);			
		inline uint16_t Combine(char high, char low){	return (((uint16_t(high) & 0x00ff ) << 8) | (uint16_t(low) & 0x00ff));	}		
		bool StrToVec(const string& str,  intvector& v);
		uint16_t  StrToInt(const string& str);
		string  VecToStr(intvector& v, int i,int j );
		string MapToJason(std::map<string,string>& dcit);
		//去括号里内容
		void Brackets(string& str);
	public://文件处理
		char* ReadLine( char* buffer, int  size, FILE *fi );
		int WiteLine( const char *str, FILE *fo );
		bool GetDirfile(std::map<string,int>& filelist, const char* path);
	public://时间处理
		string GetTime();
		string GetDate();

	public://常用模版
		template <class T> int MaxArray(T* prob, int n){
			if((n < 1 )||(prob == NULL))return -1;
			T temp = prob[0];	int index =0;
			for(int i =0; i< n; i++){
				if(temp < prob[i] ){
					temp = prob[i]; 	index = i;
				}
			}
			return index;
		}
		template <class T> int MinArray(T* prob, int n){
			if((n < 1 )||(prob == NULL))return -1;
			T temp = prob[0];	int index =0;
			for(int i =0; i< n; i++){
				if(temp > prob[i] ){
					temp = prob[i]; 	index = i;
				}
			}
			return index;
		}
		template <class T> string ConvertToStr(T value) {
			std::stringstream ss;	ss << value;	return ss.str();
		}
		static bool SortByDistance(const wdlen& x, const wdlen& y){
			return x.d > y.d;
		}
		static bool SortBySecondGreater(const std::pair<string, float>& x, 
			const std::pair<string, float>& y ){
				return x.second > y.second;
		}
		static bool SortBySecondLess(const std::pair<string, float>& x, 
			const std::pair<string, float>& y ){
				return x.second < y.second;
		}
	};
	*/

}
#endif

