#include<iostream>
#include<vector>

using namespace std;

int calProfit(const vector<int>&prices, const int size ){

	if (size <= 1)
	{
		cout << "No transaction is completed." << endl;
		return 0;
	}

		


	int maxPoint = 0, minPoint = 0, maxProfit = 0,currentMin=0;
	//分别为卖出日，买入日，最高利润以及遍历为止最小值


	for (int i = 1; i < size; i++){
		if (prices[i] < prices[currentMin])
			currentMin = i;

		else{
			if (maxProfit < prices[i] - prices[currentMin]) {
				maxProfit = prices[i] - prices[currentMin];
				maxPoint = i;
				minPoint = currentMin;
				//更新买入卖出日
				
			}
		}


	}

	if (maxProfit > 0) {
		cout << "Buy on day " << minPoint + 1 << " (price = " << prices[minPoint] << ")"
			<< " and sell on day " << maxPoint + 1 << " (price = " << prices[maxPoint] << ")" << endl;
	}
	else {
		cout << "No transaction is completed." << endl;
	}

	return maxProfit;

}





int main(){

	vector<int>prices;
	int price;
	
	cout << "====Please enter prices of each day, separating by space (input 0 to end)====" << endl;
	
	while (1) {
		cin >> price;
		if (price == 0||cin.fail())
			break;
		else
			prices.push_back(price);
	}
		
	cin.clear();

	int maxProfit=calProfit(prices, prices.size());

	cout << "Profit: " << maxProfit << endl;



	return 0;


}