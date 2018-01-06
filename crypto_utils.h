#include <cstdint>
#include <map>
#include <string>
#include <vector>

static const std::map<char, float> ascii_freq = {
	{' ', .18288},
	{'e', .10266},
	{'t', .07517},
	{'a', .06532},
	{'o', .06160},
	{'n', .05712},
	{'i', .05668},
	{'s', .05317},
	{'r', .04988},
	{'h', .04979},
	{'l', .03318},
	{'d', .03283},
	{'u', .02276},
	{'c', .02234},
	{'m', .02027},
	{'f', .01983},
	{'w', .01704},
	{'g', .01625},
	{'p', .01504},
	{'y', .01428},
	{'b', .01259},
	{'v', .00796},
	{'k', .00561},
	{'x', .00141},
	{'j', .00095},
	{'q', .00084},
	{'z', .00051}
};



int hex_to_bytes(const std::string & input, std::vector<uint8_t> & bytes);
void base64_encode(const std::vector<uint8_t> & bytes, std::vector<char> & output);
void fixed_xor(const std::vector<uint8_t> & bytes1, const std::vector<uint8_t> & bytes2,
	std::vector<uint8_t> & output);
void determine_frequencies(const std::vector<uint8_t> & bytes, std::map<char,float> & map);
float determine_chi_squared_result(const std::map<char, float> & freq);
