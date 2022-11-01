#ifndef __PROGTEST__

#include <bitset>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <climits>
#include <cmath>
#include <cassert>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <deque>
#include <deque>
#include <stack>
#include <algorithm>
#include <pthread.h>
#include <semaphore.h>
#include <cstdint>
#include <array>
#include <unordered_map>
#include <unordered_set>
#include <thread>
#include <mutex>
#include <memory>
#include <condition_variable>
#include <atomic>

using namespace std;

class CFITCoin;
class CCVUTCoin;
class CCustomer;

typedef struct shared_ptr<CFITCoin> AFITCoin;
typedef struct shared_ptr<CCVUTCoin> ACVUTCoin;
typedef struct shared_ptr<CCustomer> ACustomer;

class CFITCoin {
  public:
    CFITCoin(const vector<uint32_t> & vectors, int distMax) : m_Vectors(vectors), m_DistMax(distMax), m_Count(0) {}
    virtual ~CFITCoin() = default;
    vector<uint32_t> m_Vectors;
    int m_DistMax;
    uint64_t m_Count;
};

class CCVUTCoin {
  public:
    CCVUTCoin(const vector<uint8_t> & data, int distMin, int distMax) :
        m_Data(data), m_DistMin(distMin), m_DistMax(distMax), m_Count(0) {}

    virtual ~CCVUTCoin() = default;
    vector<uint8_t> m_Data;
    int m_DistMin;
    int m_DistMax;
    uint64_t m_Count;
};

class CCustomer {
  public:
    virtual ~CCustomer() = default;
    virtual AFITCoin FITCoinGen() = 0;
    virtual ACVUTCoin CVUTCoinGen() = 0;
    virtual void FITCoinAccept(AFITCoin x) = 0;
    virtual void CVUTCoinAccept(ACVUTCoin x) = 0;
};

#endif /* __PROGTEST__ */

class CustomerService;
class CustomerProblem;
typedef struct shared_ptr<CustomerService> ACustomerService;
typedef struct shared_ptr<CustomerProblem> ACustomerProblem;

//ewwwwww, wrote another program that generated all the numbers needed for CVUT coin, formating this is kinda waste of time
uint32_t bino[33][33] = {{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},{1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},{1,3,3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},{1,4,6,4,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},{1,5,10,10,5,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},{1,6,15,20,15,6,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},{1,7,21,35,35,21,7,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},{1,8,28,56,70,56,28,8,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},{1,9,36,84,126,126,84,36,9,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},{1,10,45,120,210,252,210,120,45,10,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},{1,11,55,165,330,462,462,330,165,55,11,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},{1,12,66,220,495,792,924,792,495,220,66,12,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},{1,13,78,286,715,1287,1716,1716,1287,715,286,78,13,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},{1,14,91,364,1001,2002,3003,3432,3003,2002,1001,364,91,14,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},{1,15,105,455,1365,3003,5005,6435,6435,5005,3003,1365,455,105,15,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},{1,16,120,560,1820,4368,8008,11440,12870,11440,8008,4368,1820,560,120,16,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},{1,17,136,680,2380,6188,12376,19448,24310,24310,19448,12376,6188,2380,680,136,17,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},{1,18,153,816,3060,8568,18564,31824,43758,48620,43758,31824,18564,8568,3060,816,153,18,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},{1,19,171,969,3876,11628,27132,50388,75582,92378,92378,75582,50388,27132,11628,3876,969,171,19,1,1,1,1,1,1,1,1,1,1,1,1,1,1},{1,20,190,1140,4845,15504,38760,77520,125970,167960,184756,167960,125970,77520,38760,15504,4845,1140,190,20,1,1,1,1,1,1,1,1,1,1,1,1,1},{1,21,210,1330,5985,20349,54264,116280,203490,293930,352716,352716,293930,203490,116280,54264,20349,5985,1330,210,21,1,1,1,1,1,1,1,1,1,1,1,1},{1,22,231,1540,7315,26334,74613,170544,319770,497420,646646,705432,646646,497420,319770,170544,74613,26334,7315,1540,231,22,1,1,1,1,1,1,1,1,1,1,1},{1,23,253,1771,8855,33649,100947,245157,490314,817190,1144066,1352078,1352078,1144066,817190,490314,245157,100947,33649,8855,1771,253,23,1,1,1,1,1,1,1,1,1,1},{1,24,276,2024,10626,42504,134596,346104,735471,1307504,1961256,2496144,2704156,2496144,1961256,1307504,735471,346104,134596,42504,10626,2024,276,24,1,1,1,1,1,1,1,1,1},{1,25,300,2300,12650,53130,177100,480700,1081575,2042975,3268760,4457400,5200300,5200300,4457400,3268760,2042975,1081575,480700,177100,53130,12650,2300,300,25,1,1,1,1,1,1,1,1},{1,26,325,2600,14950,65780,230230,657800,1562275,3124550,5311735,7726160,9657700,10400600,9657700,7726160,5311735,3124550,1562275,657800,230230,65780,14950,2600,325,26,1,1,1,1,1,1,1},{1,27,351,2925,17550,80730,296010,888030,2220075,4686825,8436285,13037895,17383860,20058300,20058300,17383860,13037895,8436285,4686825,2220075,888030,296010,80730,17550,2925,351,27,1,1,1,1,1,1},{1,28,378,3276,20475,98280,376740,1184040,3108105,6906900,13123110,21474180,30421755,37442160,40116600,37442160,30421755,21474180,13123110,6906900,3108105,1184040,376740,98280,20475,3276,378,28,1,1,1,1,1},{1,29,406,3654,23751,118755,475020,1560780,4292145,10015005,20030010,34597290,51895935,67863915,77558760,77558760,67863915,51895935,34597290,20030010,10015005,4292145,1560780,475020,118755,23751,3654,406,29,1,1,1,1},{1,30,435,4060,27405,142506,593775,2035800,5852925,14307150,30045015,54627300,86493225,119759850,145422675,155117520,145422675,119759850,86493225,54627300,30045015,14307150,5852925,2035800,593775,142506,27405,4060,435,30,1,1,1},{1,31,465,4495,31465,169911,736281,2629575,7888725,20160075,44352165,84672315,141120525,206253075,265182525,300540195,300540195,265182525,206253075,141120525,84672315,44352165,20160075,7888725,2629575,736281,169911,31465,4495,465,31,1,1},{1,32,496,4960,35960,201376,906192,3365856,10518300,28048800,64512240,129024480,225792840,347373600,471435600,565722720,601080390,565722720,471435600,347373600,225792840,129024480,64512240,28048800,10518300,3365856,906192,201376,35960,4960,496,32,1}};

uint32_t minFromThree(uint32_t a, uint32_t b, uint32_t c) {
    if (b < a) {
        a = b;
    }

    if (c < a) {
        a = c;
    }

    return a;
}

void binaryToString(uint8_t bin, string & str) {
    for (int i = 0x80; i >= 0x1; i >>= 1) {
        if (bin & i) {
            str.push_back('1');
        } else {
            str.push_back('0');
        }
    }
}

int numberOfOnes(uint32_t mask) {
    int res = 0;
    for (int i = 0; i < 32; ++i) {
        if (mask & (1 << i)) {
            ++res;
        }
    }

    return res;
}

uint32_t bitShiftByMask(uint32_t num, uint32_t mask) {
    uint32_t res = 0;
    for (int i = 0, numOfShifts = 0; i < 32; ++i) {
        if (!(mask & (1 << i))) {
            res |= (num & (1 << i)) >> (i - numOfShifts++);
        }
    }
    return res;
}



class CustomerProblem {
  public:
  	CustomerProblem() : m_firstCount(0), m_secondCount(0), m_thirdCount(0), m_fourthCount(0), m_parallelWork(0),
  						m_firstFinished(false), m_secondFinished(false), m_thirdFinished(false), m_fourthFinished(false),
  						m_customerId(-1), m_cvut(nullptr), m_fit(nullptr) {}
  	CustomerProblem(const CustomerProblem & x) {
  		m_customerId = x.m_customerId;
  		m_cvut = x.m_cvut;
  		m_fit = x.m_fit;
  	}

  	uint64_t m_firstCount;
  	uint64_t m_secondCount;
  	uint64_t m_thirdCount;
  	uint64_t m_fourthCount;
  	int m_parallelWork;

  	bool m_firstFinished;
  	bool m_secondFinished;
  	bool m_thirdFinished;
  	bool m_fourthFinished;

  	int m_customerId;
  	ACVUTCoin m_cvut;
  	AFITCoin m_fit;
};

struct CustomerData {
	CustomerData(size_t id) : m_outputBuffer(), m_coinCounter(2), m_id(id), m_outActive(true) {}

	deque<ACustomerProblem> m_outputBuffer;
	mutex mg_outputBuffer;
  condition_variable mcv_outputBuffer;
  mutex mg_paralell;
  condition_variable mcv_paralell;
	atomic_int m_coinCounter;
	size_t m_id;
  atomic_bool m_outActive;
};

class CustomerService {
  public:
  	CustomerService(ACustomer customer, size_t id);
  	~CustomerService();

  	ACustomer m_customer;
  	CustomerData m_data;

  	thread m_fitThread;
  	thread m_cvutThread;
  	thread m_outputBufferThread;
};

class CRig {
  public:
    CRig();
    ~CRig();

    static void Solve(ACVUTCoin x);
    static void Solve(AFITCoin x);
    static void SolveFIT(ACustomerProblem prbl, int state);
    static void SolveCVUT(ACustomerProblem prbl, int state);
    void Start(int thrCnt);
    void Stop();
    void AddCustomer(ACustomer c);

  private:
  	vector<thread> m_workingThreads;
  	deque<ACustomerProblem> m_workBuffer;
	  mutex mg_workBuffer;
    condition_variable mcv_workBuffer;

  	vector<ACustomerService> m_customers;

  	bool m_keepWorking;
    int m_liveCustomerCount;

    mutex mg_onEnd;
    condition_variable mcv_onEnd;
};

void solveProblems(size_t threadCount, vector<ACustomerService> & customers, deque<ACustomerProblem> & workBuffer,
                   mutex & g_workBuffer, condition_variable & cv_workBuffer, bool & keepWorking) {
	while (keepWorking) {
		ACustomerProblem x = nullptr;
		int workState = -1; //-1 = empty, 0 = regular, 1 = parallel first quarter, 2 = parallel second quarter, 3 ..., 4...

		{
      		unique_lock<mutex> m(g_workBuffer);
          while (workBuffer.empty() && keepWorking) {
            cv_workBuffer.wait(m);
          } 

          if (!keepWorking) {
            return;
          }

	      	x = workBuffer.front();

	      	if (x->m_parallelWork > 0) {
	      		//finish the solution
	      		++x->m_parallelWork;
	      		workState = x->m_parallelWork;

	      		if (workState == 4) {
	      			workBuffer.pop_front();
	      		}
	      	} else if (threadCount > workBuffer.size()) {
	      		//make first half of the solution
	      		workState = 1;
	      		x->m_parallelWork = 1;
	      	} else {
	      		workState = 0;
	      		workBuffer.pop_front();
	      	}
		}

		switch (workState) {
			case 0:
				if (x->m_cvut != nullptr) {
					CRig::Solve(x->m_cvut);
		      unique_lock<mutex> m(customers[x->m_customerId]->m_data.mg_outputBuffer);
					customers[x->m_customerId]->m_data.m_outputBuffer.push_back(x);
				} else if (x->m_fit != nullptr) {
					CRig::Solve(x->m_fit);
			    unique_lock<mutex> m(customers[x->m_customerId]->m_data.mg_outputBuffer);
					customers[x->m_customerId]->m_data.m_outputBuffer.push_back(x);
				}
        customers[x->m_customerId]->m_data.mcv_outputBuffer.notify_one();
				break;
			case 1:
				if (x->m_cvut != nullptr) {
					CRig::SolveCVUT(x, workState);
				} else if (x->m_fit != nullptr) {
					CRig::SolveFIT(x, workState);
				}
				x->m_firstFinished = true;
        customers[x->m_customerId]->m_data.mcv_paralell.notify_one();
				break;
			case 2:
				if (x->m_cvut != nullptr) {
					CRig::SolveCVUT(x, workState);
				} else if (x->m_fit != nullptr) {
					CRig::SolveFIT(x, workState);
				}
				x->m_secondFinished = true;
        customers[x->m_customerId]->m_data.mcv_paralell.notify_one();
				break;
			case 3:
				if (x->m_cvut != nullptr) {
					CRig::SolveCVUT(x, workState);
				} else if (x->m_fit != nullptr) {
					CRig::SolveFIT(x, workState);
				}
				x->m_thirdFinished = true;
        customers[x->m_customerId]->m_data.mcv_paralell.notify_one();
				break;
			case 4:
				if (x->m_cvut != nullptr) {
					CRig::SolveCVUT(x, workState);
				} else if (x->m_fit != nullptr) {
					CRig::SolveFIT(x, workState);
				}
        {
  			  unique_lock<mutex> m(customers[x->m_customerId]->m_data.mg_outputBuffer);
  				customers[x->m_customerId]->m_data.m_outputBuffer.push_back(x);
        }
  			x->m_fourthFinished = true;
        customers[x->m_customerId]->m_data.mcv_paralell.notify_one();
        customers[x->m_customerId]->m_data.mcv_outputBuffer.notify_one();
				break;
		}

	}
}

void digFit(ACustomer customer, CustomerData & data, deque<ACustomerProblem> & workBuffer, mutex & g_workBuffer, condition_variable & cv_workBuffer) {
	for (AFITCoin fitCoin = customer->FITCoinGen(); fitCoin; fitCoin = customer->FITCoinGen()) {
		ACustomerProblem tmp = make_shared<CustomerProblem>();
		tmp->m_fit = fitCoin;
		tmp->m_customerId = data.m_id;

		++data.m_coinCounter;
    unique_lock<mutex> m(g_workBuffer);
    workBuffer.push_back(tmp);
    m.unlock();
    cv_workBuffer.notify_all();
	}

  --data.m_coinCounter;
  data.mcv_outputBuffer.notify_one();
}

void digCvut(ACustomer customer, CustomerData & data, deque<ACustomerProblem> & workBuffer, mutex & g_workBuffer, condition_variable & cv_workBuffer) {
	for (ACVUTCoin cvutCoin = customer->CVUTCoinGen(); cvutCoin; cvutCoin = customer->CVUTCoinGen()) {
		ACustomerProblem tmp = make_shared<CustomerProblem>();
		tmp->m_cvut = cvutCoin;
		tmp->m_customerId = data.m_id;

		++data.m_coinCounter;
    unique_lock<mutex> m(g_workBuffer);
    workBuffer.push_back(tmp);
    m.unlock();
    cv_workBuffer.notify_all();
	}

  --data.m_coinCounter;
  data.mcv_outputBuffer.notify_one();
}

void handCoins(ACustomer customer, CustomerData & data, condition_variable & cv_onEnd) {
	while (data.m_coinCounter > 0) {
		ACustomerProblem x = nullptr;
		    {
	      	unique_lock<mutex> m(data.mg_outputBuffer);
          while (data.m_outputBuffer.empty() && data.m_coinCounter > 0) {
            data.mcv_outputBuffer.wait(m);
          }

          if (!data.m_outputBuffer.empty()) {
    	      x = data.m_outputBuffer.front();
    	      data.m_outputBuffer.pop_front();
    	      --data.m_coinCounter;
          }
        }

        if (x) {
        	if (x->m_fit != nullptr) {
        		if (x->m_parallelWork > 0) {
              unique_lock<mutex> m(data.mg_paralell);
        			while (!x->m_firstFinished || !x->m_secondFinished || !x->m_thirdFinished || !x->m_fourthFinished) {
                data.mcv_paralell.wait(m);
        			}
        			x->m_fit->m_Count = x->m_firstCount + x->m_secondCount + x->m_thirdCount + x->m_fourthCount;
        			customer->FITCoinAccept(x->m_fit);
        		} else {
        			customer->FITCoinAccept(x->m_fit);
        		}
        	} else if (x->m_cvut != nullptr) {
        		if (x->m_parallelWork > 0) {
              unique_lock<mutex> m(data.mg_paralell);
        			while (!x->m_firstFinished || !x->m_secondFinished || !x->m_thirdFinished || !x->m_fourthFinished) {
                data.mcv_paralell.wait(m);
        			}
        			x->m_cvut->m_Count = x->m_firstCount + x->m_secondCount + x->m_thirdCount + x->m_fourthCount;
        			customer->CVUTCoinAccept(x->m_cvut);
        		} else {
        			customer->CVUTCoinAccept(x->m_cvut);
        		}
        	}
        }
	}

  	data.m_outActive = false;
    cv_onEnd.notify_one();
}

#ifndef __PROGTEST__
#include "test.hpp"
#endif /* __PROGTEST__ */


CRig::CRig() : m_keepWorking(true), m_liveCustomerCount(0) {

}

CRig::~CRig() {

}

void CRig::Solve(ACVUTCoin x) {
    string prefix = "";

    for (auto binary = x->m_Data.rbegin(); binary != x->m_Data.rend(); ++binary) {
        binaryToString(*binary, prefix);
    }

    size_t prefixLength = prefix.length();

    if (x->m_DistMin >= 0 && prefixLength < (size_t)x->m_DistMin) {
    	return;
    }

    for (size_t s = 0; s < prefixLength; ++s) {
    	string suffix = prefix.substr(s);
    	size_t suffixLength = suffix.length();
    	size_t minBound = suffixLength + x->m_DistMax;
    	vector<vector<int>> dataTable;
    	dataTable.resize(prefixLength + 1, vector<int>(suffixLength + 1));

	    for (size_t i = 0; i <= prefixLength && i <= minBound; ++i) {
	        for (size_t j = 0; j <= suffixLength; ++j) {
	        	if (i == 0) {
	        		dataTable[i][j] = j;
	        	} else if (j == 0) {
	        		dataTable[i][j] = i;
	        	} else if (prefix[i - 1] == suffix[j - 1]) {
	                dataTable[i][j] = dataTable[i - 1][j - 1];
	        	} else {
	                dataTable[i][j] = 1 + minFromThree(dataTable[i][j - 1], dataTable[i - 1][j], dataTable[i - 1][j - 1]);
	        	}
	        }
	    }

	    for (size_t i = 1; i <= prefixLength && i <= minBound; ++i) {
	        if (dataTable[i][suffixLength] >= x->m_DistMin && dataTable[i][suffixLength] <= x->m_DistMax) {
	            ++x->m_Count;
	        }
	    }
    }
}

void CRig::Solve(AFITCoin x) {
    uint32_t ones_mask = 0xFFFFFFFF;
    uint32_t zeroes_mask = 0x00000000;
    uint32_t mask = 0;
    vector<uint32_t> vectors(x->m_Vectors);

    for (auto binary : vectors) {
        ones_mask &= binary;
        zeroes_mask |= binary;
    }
    mask |= ones_mask | ~zeroes_mask;

    for (auto & binary : vectors) {
        binary = bitShiftByMask(binary, mask);
    }

    int numOfIgnoredBits = numberOfOnes(mask);
    uint64_t maxIndex = 1 << (32 - numOfIgnoredBits);
    for (uint64_t i = 0; i < maxIndex; ++i) {
        bool correctRes = true;

        int worstCase = -1;
        for (auto binary : vectors) {
            int dist = numberOfOnes(binary ^ i);

            if (dist > x->m_DistMax) {
                correctRes = false;
                break;
            }

            if (dist > worstCase) {
                worstCase = dist;
            }
        }

        if (correctRes) {
            int possibleChanges = x->m_DistMax - worstCase;

            for (int k = 0; k <= possibleChanges && k <= numOfIgnoredBits; ++k) {
                x->m_Count += bino[numOfIgnoredBits][k];
            }
        }
    }
}

void CRig::SolveCVUT(ACustomerProblem prbl, int state) {
	ACVUTCoin x = prbl->m_cvut;
    string prefix = "";

    for (auto binary = x->m_Data.rbegin(); binary != x->m_Data.rend(); ++binary) {
        binaryToString(*binary, prefix);
    }

    size_t prefixLength = prefix.length();

    if (x->m_DistMin >= 0 && prefixLength < (size_t)x->m_DistMin) {
    	return;
    }

    for (size_t s = state - 1; s < prefixLength; s += 4) {
    	string suffix = prefix.substr(s);
    	size_t suffixLength = suffix.length();
    	size_t minBound = suffixLength + x->m_DistMax;
    	vector<vector<int>> dataTable;
    	dataTable.resize(prefixLength + 1, vector<int>(suffixLength + 1));

	    for (size_t i = 0; i <= prefixLength && i <= minBound; ++i) {
	        for (size_t j = 0; j <= suffixLength; ++j) {
	        	if (i == 0) {
	        		dataTable[i][j] = j;
	        	} else if (j == 0) {
	        		dataTable[i][j] = i;
	        	} else if (prefix[i - 1] == suffix[j - 1]) {
	                dataTable[i][j] = dataTable[i - 1][j - 1];
	        	} else {
	                dataTable[i][j] = 1 + minFromThree(dataTable[i][j - 1], dataTable[i - 1][j], dataTable[i - 1][j - 1]);
	        	}
	        }
	    }

	    for (size_t i = 1; i <= prefixLength && i <= minBound; ++i) {
	        if (dataTable[i][suffixLength] >= x->m_DistMin && dataTable[i][suffixLength] <= x->m_DistMax) {
	        	switch (state) {
	        		case 1:
	            		++prbl->m_firstCount;
	        			break;
	        		case 2:
	            		++prbl->m_secondCount;
	        			break;
	        		case 3:
	            		++prbl->m_thirdCount;
	        			break;
	        		case 4:
	            		++prbl->m_fourthCount;
	        			break;
	        	}
	        }
	    }
    }
}

void CRig::SolveFIT(ACustomerProblem prbl, int state) {
	AFITCoin x = prbl->m_fit;
    uint32_t ones_mask = 0xFFFFFFFF;
    uint32_t zeroes_mask = 0x00000000;
    uint32_t mask = 0;
    vector<uint32_t> vectors(x->m_Vectors);

    for (auto binary : vectors) {
        ones_mask &= binary;
        zeroes_mask |= binary;
    }
    mask |= ones_mask | ~zeroes_mask;

    for (auto & binary : vectors) {
        binary = bitShiftByMask(binary, mask);
    }

    int numOfIgnoredBits = numberOfOnes(mask);
    uint64_t maxIndex = 1 << (32 - numOfIgnoredBits);
    uint64_t fourth = maxIndex / 4;
    uint64_t i = fourth * (state - 1);
    if (maxIndex == 1 && state == 1) {
    	++fourth;
    } else if (maxIndex == 2 && state == 2) {
    	++fourth;
    }


    for ( ; i < fourth * state; ++i) {
        bool correctRes = true;

        int worstCase = -1;
        for (auto binary : vectors) {
            int dist = numberOfOnes(binary ^ i);

            if (dist > x->m_DistMax) {
                correctRes = false;
                break;
            }

            if (dist > worstCase) {
                worstCase = dist;
            }
        }

        if (correctRes) {
            int possibleChanges = x->m_DistMax - worstCase;

            for (int k = 0; k <= possibleChanges && k <= numOfIgnoredBits; ++k) {
            	switch (state) {
	        		case 1:
	            		prbl->m_firstCount += bino[numOfIgnoredBits][k];
	        			break;
	        		case 2:
	            		prbl->m_secondCount += bino[numOfIgnoredBits][k];
	        			break;
	        		case 3:
	            		prbl->m_thirdCount += bino[numOfIgnoredBits][k];
	        			break;
	        		case 4:
	            		prbl->m_fourthCount += bino[numOfIgnoredBits][k];
	        			break;
	        	}
            }
        }
    }
}

void CRig::Start(int thrCnt) {
	for (int i = 0; i < thrCnt; ++i) {
		m_workingThreads.push_back(thread(solveProblems, thrCnt, ref(m_customers), ref(m_workBuffer), ref(mg_workBuffer), ref(mcv_workBuffer), ref(m_keepWorking)));
	}
}

void CRig::Stop() {
	for (auto & cust : m_customers) {
	  	cust->m_fitThread.join();
	  	cust->m_cvutThread.join();
	  	cust->m_outputBufferThread.join();
	}

	m_keepWorking = false;
  mcv_workBuffer.notify_all();

	for (auto & thread : m_workingThreads) {
		thread.join();
	}
}

//max 7
void CRig::AddCustomer(ACustomer c) {
	  size_t size = m_customers.size();

    unique_lock<mutex> m(mg_onEnd);
  	while (m_liveCustomerCount >= 7) {
     	for (size_t i = 0; i < m_customers.size(); ++i) {
        	if (!m_customers[i]->m_data.m_outActive) {
        		  m_customers[i]->m_fitThread.join();
        	  	m_customers[i]->m_cvutThread.join();
        	  	m_customers[i]->m_outputBufferThread.join();

	            ACustomerService tmp = make_shared<CustomerService>(c, i);
	            m_customers[i] = tmp;
	            m_customers[i]->m_fitThread = thread(digFit, c, ref(m_customers[i]->m_data), ref(m_workBuffer), ref(mg_workBuffer), ref(mcv_workBuffer));
	            m_customers[i]->m_cvutThread = thread(digCvut, c, ref(m_customers[i]->m_data), ref(m_workBuffer), ref(mg_workBuffer), ref(mcv_workBuffer));
	            m_customers[i]->m_outputBufferThread = thread(handCoins, c, ref(m_customers[i]->m_data), ref(mcv_onEnd));

              	return;
          	}
      	}
        mcv_onEnd.wait(m);
  	}

  	++m_liveCustomerCount;
	m_customers.emplace_back(make_shared<CustomerService>(c, size));
	m_customers[size]->m_fitThread = thread(digFit, c, ref(m_customers[size]->m_data), ref(m_workBuffer), ref(mg_workBuffer), ref(mcv_workBuffer));
  m_customers[size]->m_cvutThread = thread(digCvut, c, ref(m_customers[size]->m_data), ref(m_workBuffer), ref(mg_workBuffer), ref(mcv_workBuffer));
  m_customers[size]->m_outputBufferThread = thread(handCoins, c, ref(m_customers[size]->m_data), ref(mcv_onEnd));
}

CustomerService::CustomerService(ACustomer customer, size_t id)
  : m_customer(customer), m_data(id) {}

CustomerService::~CustomerService() {}