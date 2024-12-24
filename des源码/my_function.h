#ifndef		MY_FUNCTION_H
#define		MY_FUNCTION_H

typedef unsigned char       UCHAR;
typedef unsigned short      USHORT;


#define ENCRYPT		1
#define DECRYPT		0

#define FALSE		0
#define TRUE		1		

#define DES_1		1					//1DES算法
#define DES_2		2					//2DES算法
#define DES_3		3					//3DES算法

#define BYTE_8		'1'					//分散数据8字节
#define BYTE_16		'2'					//分散数据16字节

class MY_FUNCTION //:public CDialog
{
protected:



public:
	void set_key( unsigned char *key);
	void des_crypt(unsigned char crypt_flag, unsigned char *text, unsigned char *result);
    void Encrypt( unsigned char keyflag,  unsigned char *key,  int length,  unsigned char *text,  unsigned char *result);
	void Decrypt( unsigned char keyflag,  unsigned char *key,  int length,  unsigned char *text,  unsigned char *result);
	void EncryptCBC(unsigned char keyflag, unsigned char* key, unsigned char* iv, int length, unsigned char* text, unsigned char* result);
	void DecryptCBC(unsigned char keyflag, unsigned char* key, unsigned char* iv, int length, unsigned char* text, unsigned char* result);
	unsigned char mac_encrypt_919( unsigned char keyflag,  unsigned char *key, int text_bytes,  unsigned char *text,  unsigned char *mac);
	void EMacX99 ( unsigned char keyflag,  unsigned char *key,  int text_bytes,  unsigned char *text,  unsigned char *mac);
	void GetCheckValue( unsigned char keyflag,  unsigned char *key,  unsigned char *check);
	void Hex2Ascii(int len, unsigned char *InBuf, unsigned char *OutBuf);
	void Ascii2Hex(int len, unsigned char *InBuf, unsigned char *OutBuf);
	unsigned char key_dive(unsigned char flag, unsigned char keyfalg,unsigned char keylen, unsigned char *key, int datalen, unsigned char *data, unsigned char *resulte);
	void Byte2String(short len, unsigned char *InBuf, unsigned char *OutBuf);
	void String2Byte(short len, unsigned char *InBuf, unsigned char *OutBuf);
	unsigned char data_en_de(unsigned char flag, unsigned char keyflag, UCHAR *key, int datalen, UCHAR *data, UCHAR *resulte);
	unsigned char mac_919_cal(unsigned char keyflag, UCHAR *key, UCHAR *begin_vector,int datalen, UCHAR *data, UCHAR *mac);
	unsigned char key_dive_hex(char unsigned flag, unsigned char keyfalg, unsigned char *key, int datalen, unsigned char *data, unsigned char *resulte);
	unsigned char data_en_de_hex(unsigned char flag, unsigned char keyflag, UCHAR *key, int datalen, UCHAR *data, UCHAR *resulte);
	unsigned char mac_919_cal_hex(unsigned char keyflag, UCHAR *key, UCHAR *begin_vector,int datalen, UCHAR *data, UCHAR *mac);


	FILE *pBackup;
	FILE *pRead;
};
#endif