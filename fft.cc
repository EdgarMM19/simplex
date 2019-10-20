#include <bits/stdc++.h>
#include "Bigint.hh"
using namespace std;

const ld pi = 3.14159265358979323846264338;

Bigint::comp Bigint::cmult(Bigint::comp a, Bigint::comp b){
	Bigint::comp c;
	c.r=a.r*b.r-a.c*b.c;
	c.c=a.c*b.r+a.r*b.c;
	return c;
}

ll Bigint::creverse(ll a, ll p){
	ll s=0;
	while(p--){
		s=(s<<1);
		if(a&1) s^=1;
		a=(a>>1);
	}
	return s;
}

vector <Bigint::comp> Bigint::fft(vector <Bigint::comp>v, ll m, ll p){
	vector <Bigint::comp>x(m);
	for(ll i=0;i<m;++i){
		x[i]=v[creverse(i, p)];
	}
	ll t=1;
	for(ll i=1;i<=p;++i){
		t=(t<<1);
		Bigint::comp w;
		w.r=cos(2*pi/t);
		w.c=sin(2*pi/t);
		for(ll k=0;k<m;k+=t){
			Bigint::comp r;
			r.r=1;
			r.c=0;
			for(ll j=0;j<t/2;++j){
				Bigint::comp y=cmult(r, x[k+j+t/2]);
				Bigint::comp z=x[k+j];
				x[k+j].r=y.r+z.r;
				x[k+j].c=y.c+z.c;
				x[k+j+t/2].r=z.r-y.r;
				x[k+j+t/2].c=z.c-y.c;
				r=cmult(r, w);
			}
		}	
	}
	return x;
}

vector <Bigint::comp> Bigint::ifft(vector <Bigint::comp>v, ll m, ll p){
	vector <Bigint::comp>x(m);
	for(ll i=0;i<m;++i){
		x[i]=v[creverse(i, p)];
	}
	ll t=1;
	for(ll i=1;i<=p;++i){
		t=(t<<1);
		Bigint::comp w;
		w.r=cos(2*pi/t);
		w.c=-sin(2*pi/t);
		for(ll k=0;k<m;k+=t){
			Bigint::comp r;
			r.r=1;
			r.c=0;
			for(ll j=0;j<t/2;++j){
				Bigint::comp y=cmult(r, x[k+j+t/2]);
				Bigint::comp z=x[k+j];
				x[k+j].r=y.r+z.r;
				x[k+j].c=y.c+z.c;
				x[k+j+t/2].r=z.r-y.r;
				x[k+j+t/2].c=z.c-y.c;
				r=cmult(r, w);
			}
		}	
	}
	for(ll i=0;i<m;++i){
		x[i].r/=m;
		x[i].c/=m;
	}
	return x;
}

vector<ll> Bigint::__mult__(const vll& s, const vll& t) {
	ll m = 1;
	ll p = 0;
	while(m<s.size()+t.size()){
		m=(m<<1);
		++p;
	}
	vector<Bigint::comp> n1(m);
	for(ll i=0; i<(ll)s.size(); i++){
		n1[i].r = s[i];
		n1[i].c = 0.0;
	}
	for(ll i=(ll)s.size(); i<m; i++){
		n1[i].r = 0.0;
		n1[i].c = 0.0;
	}
	vector<Bigint::comp> n2(m);
	for(ll i=0; i<(ll)t.size(); i++){
		n2[i].r = t[i];
		n2[i].c = 0.0;
	}
	for(ll i=(ll)t.size(); i<m; i++){
		n2[i].r = 0.0;
		n2[i].c = 0.0;
	}
	n1 = fft(n1, m, p);
	n2 = fft(n2, m, p);

	for(ll i=0; i<m; ++i){
		n1[i] = cmult(n1[i], n2[i]);
	}
	n1 = ifft(n1, m, p);
	vector<ll> ans(m);
	ans[0]=0;
	for(ll i=0; i<m-1; i++){
		ans[i] += ll(n1[i].r+1e-5);
		ans[i+1] = ans[i]/BASE;
		ans[i] %= BASE;
	}
	ans[m-1] += ll(n1[m-1].r+1e-5);
	while (ans.back() == 0 and ans.size() >= 2) ans.pop_back();
	return ans;
}
