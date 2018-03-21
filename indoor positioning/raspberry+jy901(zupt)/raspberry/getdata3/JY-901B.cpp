#include "JY-901B.h"
#include "string.h"

CJY901::CJY901(unsigned char bus, unsigned char devAddr) {
	I2CBus = bus;
	I2CAddress = devAddr;
	I2CFileDescriptor = -1;
	printf("JY901 at addr:%2X on bus: %i was initialized\n", I2CAddress,
			I2CBus);
}

bool CJY901::Open() {
	printf("Trying to open bus: %i:", I2CBus);
	char fileNameBuffer[32];
	sprintf(fileNameBuffer, "/dev/i2c-%d", I2CBus);
	I2CFileDescriptor = open(fileNameBuffer, O_RDWR);
	if (I2CFileDescriptor < 0) {
		// Could not open the file
		printf("Can't open file: %s\n", fileNameBuffer);
		return false;
	} else
		printf("SUCCESS!\n");

	printf("Trying to open Dev at addr:%2X on bus: %i:", I2CAddress, I2CBus);
	if (ioctl(I2CFileDescriptor, I2C_SLAVE, I2CAddress) < 0) {
		// Could not open the device on the bus
		printf("Can't open addr:%2X on bus: %i\n", I2CAddress, I2CBus);
		return false;
	} else
		printf("SUCCESS!\n");
	return true;
}

void CJY901::GetTime() {
	i2c_smbus_read_i2c_block_data(I2CFileDescriptor, 0x30, 8,
			(unsigned char*) &stcTime);
}
void CJY901::GetAcc() {
	i2c_smbus_read_i2c_block_data(I2CFileDescriptor, AX, 6,
			(unsigned char *) &stcAcc);
}
void CJY901::GetAcc_bias(){
    i2c_smbus_read_i2c_block_data(I2CFileDescriptor,AXOFFSET,6,
            (unsigned char *) &stcAcc_bias);
}
void CJY901::GetGyro() {
	i2c_smbus_read_i2c_block_data(I2CFileDescriptor, GX, 6,
			(unsigned char *) &stcGyro);
}
void CJY901::GetGyro_bias(){
    i2c_smbus_read_i2c_block_data(I2CFileDescriptor,GXOFFSET,6,
            (unsigned char *) &stcGyro_bias);
}
void CJY901::GetAngle() {
	i2c_smbus_read_i2c_block_data(I2CFileDescriptor, Roll, 6,
			(unsigned char *) &stcAngle);
}
void CJY901::GetMag() {
	i2c_smbus_read_i2c_block_data(I2CFileDescriptor, HX, 6,
			(unsigned char *) &stcMag);
}
void CJY901::GetMag_bias(){
    i2c_smbus_read_i2c_block_data(I2CFileDescriptor,HXOFFSET,6,
            (unsigned char *)&stcMag_bias);
}
void CJY901::GetPress() {
	i2c_smbus_read_i2c_block_data(I2CFileDescriptor, PressureL, 8,
			(unsigned char *) &stcPress);
}
void CJY901::GetDStatus() {
	i2c_smbus_read_i2c_block_data(I2CFileDescriptor, D0Status, 8,
			(unsigned char *) &stcDStatus);
}
void CJY901::GetLonLat() {
	i2c_smbus_read_i2c_block_data(I2CFileDescriptor, LonL, 8,
			(unsigned char *) &stcLonLat);
}
void CJY901::GetGPSV() {
	i2c_smbus_read_i2c_block_data(I2CFileDescriptor, GPSHeight, 8,
			(unsigned char *) &stcGPSV);
}
