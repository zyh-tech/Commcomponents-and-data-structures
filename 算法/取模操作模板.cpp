#include<bits/stdc++.h>
using namespace std;
const int mod = 1e9 + 7;
// -----取模操作模板----- 建议使用long long 实例化，最稳
template <typename T>
class Mod{
public:
	T add (T x , T y , T mod){
		x %= mod;
		y %= mod;
		T res = (x + y) % mod;
		return res;
	}
	T sub (T x , T y , T mod){
		x %= mod;
		y %= mod;
		T res = (x - y + mod) % mod;
		return res;
	}
	T mul (T x , T y , T mod){
		x %= mod;
		y %= mod;
        T res = x * y % mod;
        return res;
	}
	T div (T x , T y , T mod){
		x %= mod;
		y %= mod;
        T inv = fastPow(y , mod - 2 , mod);
        T res = mul(x , inv , mod);
        return res;
	}
private:
	T fastPow (T a , T b , T mod){
        T ans = 1 , base = a;
        while (b){
            if (b & 1) ans = mul(ans , base , mod);
            base = mul(base , base , mod);
            b >>= 1;
        }
        return ans;
	}
};
// -----取模操作模板 end-----
int main (){
	int n;
    Mod<long long> t;
	cin >> n;
	for (int i = 1 ; i <= n ; i++){
		int op;
		long long x , y;
		cin >> op >> x >> y;
		if (op == 1){
            cout << t.add(x , y , mod) << endl;
		}else if (op == 2){
            cout << t.sub(x , y , mod) << endl;
		}else if (op == 3){
            cout << t.mul(x , y , mod) << endl;
		}else {
            cout << t.div(x , y , mod) << endl;
		}
	}
}
