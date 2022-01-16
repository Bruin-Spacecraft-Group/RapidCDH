#ifndef ADS7828
#define ADS7828

#include <cstdint>

class ADS7828 {
public:
	ADS7828(const char* device, bool addr0, bool addr1, double referenceVoltage = 2.5);
	[[nodiscard]] Status init();
	[[nodiscard]] Status readChannelCommonAnode(int channel, double& value);
	[[nodiscard]] Status readChannelDifferentialPair(int pair, bool inverted, double& value);
	[[nodiscard]] Status readChannelDifferentialPair(int pair, double& value);
	[[nodiscard]] Status setRunning(bool running);
private:
	double referenceVoltage;
	uint8_t lastCmd;
	int fd;
}

#endif