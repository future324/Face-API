#include<opencv2/opencv.hpp>  
#include<iostream>  
#include<vector>  
#include<string>  
#include"curl/curl.h"
#include"Zbase64.h"
//#pragma warning (push)
//#pragma warning (disable: 4996)
#include"json/json.h"
//#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")
using namespace std;
using namespace cv;
#pragma comment(lib,"lib_json.lib")
#pragma comment(lib,"LIBCURL.LIB")

string outer_id = "firstfaceset_token";
int writer(char *data, size_t size, size_t nmemb, string *writerData)
{
	if (writerData == NULL)
		return 0;
	int len = size*nmemb;
	writerData->append(data, len);
	return len;
}
class faceplusplusApi
{
public:
	faceplusplusApi();
	~faceplusplusApi();
	string faceDetect(Mat inputimg);
	string faceSetuserid(string face_token,string user_id);
	void facesetCreate();
	void facesetUpdate(string faceset_token);
	void facesetAdd( string face_tokens);
	void facesetRemove();
	int faceCompare(Mat inputimg, Mat compareimg);
	string faceSearch(string face_tokens);
private:
	
};

faceplusplusApi::faceplusplusApi()
{
	
	
}

faceplusplusApi::~faceplusplusApi()
{
}
inline string faceplusplusApi::faceDetect(Mat inputimg)
{
	CURL *curl;
	CURLcode res;
	struct curl_slist *http_header = NULL;
	struct curl_httppost *formpost = 0;
	struct curl_httppost *lastptr = 0;
	string buffer;
	curl = curl_easy_init();
	vector<uchar> vecSrc;                               //Mat 图片数据转换为vector<uchar>  
	vector<int> vecCompression_params;
	vecCompression_params.push_back(CV_IMWRITE_JPEG_QUALITY);
	vecCompression_params.push_back(90);
	imencode(".jpg", inputimg, vecSrc, vecCompression_params);

	ZBase64 base64;
	String img_base64 = base64.Encode(vecSrc.data(), vecSrc.size());     //实现图片的base64编码  
	curl_formadd(&formpost,
		&lastptr,
		CURLFORM_COPYNAME, "api_key",
		CURLFORM_COPYCONTENTS, "jlgTxl2mUrOoYrCOy39lKmCNsCmbZ0Nw",
		CURLFORM_END);
	curl_formadd(&formpost,
		&lastptr,
		CURLFORM_COPYNAME, "api_secret",
		CURLFORM_COPYCONTENTS, "ROU_X2AD0dtwV78NTu9mRqpqz4O89rVu",
		CURLFORM_END);
	curl_formadd(&formpost,
		&lastptr,
		CURLFORM_COPYNAME, "image_base64",
		CURLFORM_COPYCONTENTS, img_base64.c_str(),
		CURLFORM_END);


	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writer);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);
	curl_easy_setopt(curl, CURLOPT_URL, "https://api-cn.faceplusplus.com/facepp/v3/detect");
	curl_easy_setopt(curl, CURLOPT_HTTPPOST, formpost);
	res = curl_easy_perform(curl);
	curl_easy_cleanup(curl);


	Json::Value root;
	Json::Reader reader;
	bool parsingSuccessful = reader.parse(buffer, root);

	if (!parsingSuccessful)
	{
		cout << "Failed to parse the data!" << endl;
		exit(0);
	}

	return root["faces"][0]["face_token"].asString();
}

inline string faceplusplusApi::faceSetuserid(string face_token, string user_id)
{
	string buffer;
	CURL *curl;
	CURLcode res;
	struct curl_slist *http_header = NULL;
	struct curl_httppost *formpost = 0;
	struct curl_httppost *lastptr = 0;
	curl = curl_easy_init();
	curl_formadd(&formpost,
		&lastptr,
		CURLFORM_COPYNAME, "api_key",
		CURLFORM_COPYCONTENTS, "jlgTxl2mUrOoYrCOy39lKmCNsCmbZ0Nw",
		CURLFORM_END);
	curl_formadd(&formpost,
		&lastptr,
		CURLFORM_COPYNAME, "api_secret",
		CURLFORM_COPYCONTENTS, "ROU_X2AD0dtwV78NTu9mRqpqz4O89rVu",
		CURLFORM_END);
	curl_formadd(&formpost,
		&lastptr,
		CURLFORM_COPYNAME, "face_token",
		CURLFORM_COPYCONTENTS, face_token.c_str(),
		CURLFORM_END);

	curl_formadd(&formpost,
		&lastptr,
		CURLFORM_COPYNAME, "user_id",
		CURLFORM_COPYCONTENTS, user_id.c_str(),
		CURLFORM_END);

	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writer);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);
	curl_easy_setopt(curl, CURLOPT_URL, "https://api-cn.faceplusplus.com/facepp/v3/face/setuserid");
	curl_easy_setopt(curl, CURLOPT_HTTPPOST, formpost);
	res = curl_easy_perform(curl);
	curl_easy_cleanup(curl);

	Json::Value root;
	Json::Reader reader;
	bool parsingSuccessful = reader.parse(buffer, root);

	if (!parsingSuccessful)
	{
		cout << "Failed to parse the data!" << endl;
		//system("pause");
		//exit(0);
	}
	//cout << buffer << endl;
	return "";
	//return root["user_id"].asString();
}

inline void faceplusplusApi::facesetCreate()
{
	CURL *curl;
	CURLcode res;
	struct curl_slist *http_header = NULL;
	struct curl_httppost *formpost = 0;
	struct curl_httppost *lastptr = 0;
	string buffer;

	curl = curl_easy_init();
	curl_formadd(&formpost,
		&lastptr,
		CURLFORM_COPYNAME, "api_key",
		CURLFORM_COPYCONTENTS, "jlgTxl2mUrOoYrCOy39lKmCNsCmbZ0Nw",
		CURLFORM_END);
	curl_formadd(&formpost,
		&lastptr,
		CURLFORM_COPYNAME, "api_secret",
		CURLFORM_COPYCONTENTS, "ROU_X2AD0dtwV78NTu9mRqpqz4O89rVu",
		CURLFORM_END);
	curl_formadd(&formpost,
		&lastptr,
		CURLFORM_COPYNAME, "outer_id",
		CURLFORM_COPYCONTENTS, outer_id.c_str(),
		CURLFORM_END);

	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writer);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);
	curl_easy_setopt(curl, CURLOPT_URL, "https://api-cn.faceplusplus.com/facepp/v3/faceset/create");
	curl_easy_setopt(curl, CURLOPT_HTTPPOST, formpost);
	res = curl_easy_perform(curl);
	curl_easy_cleanup(curl);

	Json::Value root;
	Json::Reader reader;
	bool parsingSuccessful = reader.parse(buffer, root);

	if (!parsingSuccessful)
	{
		cout << "Failed to parse the data!" << endl;
		exit(0);
	}
	//cout << root["faceset_token"].asString();
	
}

inline void faceplusplusApi::facesetUpdate(string faceset_token)
{
	string buffer;
	CURL *curl;
	CURLcode res;
	struct curl_slist *http_header = NULL;
	struct curl_httppost *formpost = 0;
	struct curl_httppost *lastptr = 0;
	curl = curl_easy_init();
	curl_formadd(&formpost,
		&lastptr,
		CURLFORM_COPYNAME, "api_key",
		CURLFORM_COPYCONTENTS, "jlgTxl2mUrOoYrCOy39lKmCNsCmbZ0Nw",
		CURLFORM_END);
	curl_formadd(&formpost,
		&lastptr,
		CURLFORM_COPYNAME, "api_secret",
		CURLFORM_COPYCONTENTS, "ROU_X2AD0dtwV78NTu9mRqpqz4O89rVu",
		CURLFORM_END);
	curl_formadd(&formpost,
		&lastptr,
		CURLFORM_COPYNAME, "outer_id",
		CURLFORM_COPYCONTENTS, outer_id.c_str(),
		CURLFORM_END);

	curl_formadd(&formpost,
		&lastptr,
		CURLFORM_COPYNAME, "display_name",
		CURLFORM_COPYCONTENTS, "firstfaceset_token",
		CURLFORM_END);

	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writer);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);
	curl_easy_setopt(curl, CURLOPT_URL, "https://api-cn.faceplusplus.com/facepp/v3/faceset/addface");
	curl_easy_setopt(curl, CURLOPT_HTTPPOST, formpost);
	res = curl_easy_perform(curl);
	curl_easy_cleanup(curl);

	Json::Value root;
	Json::Reader reader;
	bool parsingSuccessful = reader.parse(buffer, root);

	if (!parsingSuccessful)
	{
		cout << "Failed to parse the data!" << endl;
		//system("pause");
		//exit(0);
	}
}

inline void faceplusplusApi::facesetAdd(string face_tokens)
{
	string buffer;
	CURL *curl;
	CURLcode res;
	struct curl_slist *http_header = NULL;
	struct curl_httppost *formpost = 0;
	struct curl_httppost *lastptr = 0;
	curl = curl_easy_init();
	curl_formadd(&formpost,
		&lastptr,
		CURLFORM_COPYNAME, "api_key",
		CURLFORM_COPYCONTENTS, "jlgTxl2mUrOoYrCOy39lKmCNsCmbZ0Nw",
		CURLFORM_END);
	curl_formadd(&formpost,
		&lastptr,
		CURLFORM_COPYNAME, "api_secret",
		CURLFORM_COPYCONTENTS, "ROU_X2AD0dtwV78NTu9mRqpqz4O89rVu",
		CURLFORM_END);
	curl_formadd(&formpost,
		&lastptr,
		CURLFORM_COPYNAME, "outer_id",
		CURLFORM_COPYCONTENTS, outer_id.c_str(),
		CURLFORM_END);

	curl_formadd(&formpost,
		&lastptr,
		CURLFORM_COPYNAME, "face_tokens",
		CURLFORM_COPYCONTENTS, face_tokens.c_str(),
		CURLFORM_END);

	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writer);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);
	curl_easy_setopt(curl, CURLOPT_URL, "https://api-cn.faceplusplus.com/facepp/v3/faceset/addface");
	curl_easy_setopt(curl, CURLOPT_HTTPPOST, formpost);
	res = curl_easy_perform(curl);
	curl_easy_cleanup(curl);

	Json::Value root;
	Json::Reader reader;
	bool parsingSuccessful = reader.parse(buffer, root);

	if (!parsingSuccessful)
	{
		cout << "Failed to parse the data!" << endl;
		//system("pause");
		//exit(0);
	}
	//cout << buffer<<endl;
}

inline void faceplusplusApi::facesetRemove()
{
	string buffer;
	CURL *curl;
	CURLcode res;
	struct curl_slist *http_header = NULL;
	struct curl_httppost *formpost = 0;
	struct curl_httppost *lastptr = 0;
	curl = curl_easy_init();
	curl_formadd(&formpost,
		&lastptr,
		CURLFORM_COPYNAME, "api_key",
		CURLFORM_COPYCONTENTS, "jlgTxl2mUrOoYrCOy39lKmCNsCmbZ0Nw",
		CURLFORM_END);
	curl_formadd(&formpost,
		&lastptr,
		CURLFORM_COPYNAME, "api_secret",
		CURLFORM_COPYCONTENTS, "ROU_X2AD0dtwV78NTu9mRqpqz4O89rVu",
		CURLFORM_END);
	curl_formadd(&formpost,
		&lastptr,
		CURLFORM_COPYNAME, "outer_id",
		CURLFORM_COPYCONTENTS, outer_id.c_str(),
		CURLFORM_END);

	curl_formadd(&formpost,
		&lastptr,
		CURLFORM_COPYNAME, "face_tokens",
		CURLFORM_COPYCONTENTS, "RemoveAllFaceTokens",
		CURLFORM_END);

	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writer);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);
	curl_easy_setopt(curl, CURLOPT_URL, "https://api-cn.faceplusplus.com/facepp/v3/faceset/removeface");
	curl_easy_setopt(curl, CURLOPT_HTTPPOST, formpost);
	res = curl_easy_perform(curl);
	curl_easy_cleanup(curl);

	Json::Value root;
	Json::Reader reader;
	bool parsingSuccessful = reader.parse(buffer, root);

	if (!parsingSuccessful)
	{
		cout << "Failed to parse the data!" << endl;
		//system("pause");
		//exit(0);
	}
	//cout << buffer<<endl;
}

inline int faceplusplusApi::faceCompare(Mat inputimg, Mat compareimg)
{
	string buffer;
	CURL *curl;
	CURLcode res;
	struct curl_slist *http_header = NULL;
	struct curl_httppost *formpost = 0;
	struct curl_httppost *lastptr = 0;
	curl = curl_easy_init();
	vector<uchar> vecSrc, vecComp;                               //Mat 图片数据转换为vector<uchar>  
	vector<int> vecCompression_params;
	vecCompression_params.push_back(CV_IMWRITE_JPEG_QUALITY);
	vecCompression_params.push_back(90);
	imencode(".jpg", inputimg, vecSrc, vecCompression_params);
	imencode(".jpg", compareimg, vecComp, vecCompression_params);

	ZBase64 base64;
	String Src_base64 = base64.Encode(vecSrc.data(), vecSrc.size());     //实现图片的base64编码  
	String Comp_base64 = base64.Encode(vecComp.data(), vecComp.size());
	curl_formadd(&formpost,
		&lastptr,
		CURLFORM_COPYNAME, "api_key",
		CURLFORM_COPYCONTENTS, "jlgTxl2mUrOoYrCOy39lKmCNsCmbZ0Nw",
		CURLFORM_END);
	curl_formadd(&formpost,
		&lastptr,
		CURLFORM_COPYNAME, "api_secret",
		CURLFORM_COPYCONTENTS, "ROU_X2AD0dtwV78NTu9mRqpqz4O89rVu",
		CURLFORM_END);
	curl_formadd(&formpost,
		&lastptr,
		CURLFORM_COPYNAME, "image_base64_1",
		CURLFORM_COPYCONTENTS, Src_base64.c_str(),
		CURLFORM_END);
	curl_formadd(&formpost,
		&lastptr,
		CURLFORM_COPYNAME, "image_base64_2",
		CURLFORM_COPYCONTENTS, Comp_base64.c_str(),
		CURLFORM_END);

	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writer);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);
	curl_easy_setopt(curl, CURLOPT_URL, "https://api-cn.faceplusplus.com/facepp/v3/compare");
	curl_easy_setopt(curl, CURLOPT_HTTPPOST, formpost);
	res = curl_easy_perform(curl);
	curl_easy_cleanup(curl);


	Json::Value root;
	Json::Reader reader;
	bool parsingSuccessful = reader.parse(buffer, root);

	if (!parsingSuccessful)
	{
		cout << "Failed to parse the data!" << endl;
		exit(0);
	}

	int out = root["confidence"].asInt();
	//cout << out << endl;
	return out;
}

inline string faceplusplusApi::faceSearch(string face_tokens)
{
	string buffer;
	CURL *curl;
	CURLcode res;
	struct curl_slist *http_header = NULL;
	struct curl_httppost *formpost = 0;
	struct curl_httppost *lastptr = 0;
	curl = curl_easy_init();
	curl_formadd(&formpost,
		&lastptr,
		CURLFORM_COPYNAME, "api_key",
		CURLFORM_COPYCONTENTS, "jlgTxl2mUrOoYrCOy39lKmCNsCmbZ0Nw",
		CURLFORM_END);
	curl_formadd(&formpost,
		&lastptr,
		CURLFORM_COPYNAME, "api_secret",
		CURLFORM_COPYCONTENTS, "ROU_X2AD0dtwV78NTu9mRqpqz4O89rVu",
		CURLFORM_END);
	curl_formadd(&formpost,
		&lastptr,
		CURLFORM_COPYNAME, "face_token",
		CURLFORM_COPYCONTENTS, face_tokens.c_str(),
		CURLFORM_END);

	curl_formadd(&formpost,
		&lastptr,
		CURLFORM_COPYNAME, "outer_id",
		CURLFORM_COPYCONTENTS, outer_id.c_str(),
		CURLFORM_END);

	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writer);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);
	curl_easy_setopt(curl, CURLOPT_URL, "https://api-cn.faceplusplus.com/facepp/v3/search");
	curl_easy_setopt(curl, CURLOPT_HTTPPOST, formpost);
	res = curl_easy_perform(curl);
	curl_easy_cleanup(curl);

	Json::Value root;
	Json::Reader reader;
	bool parsingSuccessful = reader.parse(buffer, root);

	if (!parsingSuccessful)
	{
		cout << "Failed to parse the data!" << endl;
		exit(0);
	}
	cout << buffer;
	return buffer;
}
 