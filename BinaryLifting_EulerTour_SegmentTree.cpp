#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double lld;
#define pll pair<ll,ll>
#define vll vector<ll>
#define  ln "\n"
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define be begin
#define ub upper_bound
#define lb lower_bound
#define bi binary_search
#define sll set <ll>
#define msll multiset <ll>
#define vpll vector <pair<ll,ll>>
#define mll  map <ll,ll>
#define all(v) v.begin(),v.end()
#define mem1(a)  memset(a,-1,sizeof(a))
#define mem0(a)  memset(a,0,sizeof(a))
#define i1(x) cin>>x
#define i2(x1,x2) cin>>x1>>x2
#define i3(x1,x2,x3) cin>>x1>>x2>>x3
#define i4(x1,x2,x3,x4) cin>>x1>>x2>>x3>>x4
#define o1(x) cout<<x<<ln
#define o2(x1,x2) cout<<x1<<" "<<x2<<ln
#define o3(x1,x2,x3) cout<<x1<<" "<<x2<<" "<<x3<<ln
#define o4(x1,x2,x3,x4) cout<<x1<<" "<<x2<<" "<<x3<<" "<<x4<<ln
#define rep(i,s,e) for(ll i=s;i<e;i++)
#define rrep(i,s,e) for(ll i=s-1;i>=e;i--)
#define geta(a,n) for(ll i=0;i<n;i++)cin>>a[i];
const ll mod = 1e9 + 7;
mll end_st;
ll current = 0;
ll mxn = 4 * 1e5;
vpll adj[200100];
vll dfs_route;
vector <ll> t(4 * mxn, 0);
vll st(200100);
vll en(200100);
vll parent(200100);
ll timer = 0;
void dfs(ll x, ll p)
{	// euler tour
	st[x] = timer++;
	for (const auto &e : adj[x])
	{
		if (e.fi != p)
		{
			parent[e.fi] = x;
			dfs(e.fi, x);
		}
	}
	en[x] = timer;
}

void build(vll &mod, ll v, ll tl, ll tr)
{
	if (tl == tr) {
		t[v] = mod[tl];
	} else {
		ll tm = (tl + tr) / 2;
		build(mod, v * 2, tl, tm);
		build(mod, v * 2 + 1, tm + 1, tr);
		t[v] = t[v * 2] + t[v * 2 + 1];
	}
}
ll sum(ll v, ll tl, ll tr, ll l, ll r)
{
	if (l > r)
		return 0;
	if (l == tl && r == tr)
	{
		return t[v];
	}
	ll tm = (tl + tr) / 2;
	return sum(v * 2, tl, tm, l, min(r, tm)) + sum(v * 2 + 1, tm + 1, tr, max(l, tm + 1ll), r);
}
void update(ll v, ll tl, ll tr, ll pos, ll new_val)
{
	if (tl == tr)
	{
		t[v] += new_val;
	}
	else
	{
		ll tm = (tl + tr) / 2;
		if (pos <= tm)
			update(v * 2, tl, tm, pos, new_val);
		else
			update(v * 2 + 1, tm + 1, tr, pos, new_val);
		t[v] = t[v * 2] + t[v * 2 + 1];
	}
}
ll chk = 0;
void build_up(ll u, ll v,  vector <vll> &up)
{
	//o1(u);
	up[u][0] = v;
	rep(i, 1, 20)
	{
		if (up[u][i - 1] != -1)
			up[u][i] = up[up[u][i - 1]][i - 1];
		else
			up[u][i] = -1;
	}
	for (auto i : adj[u])
	{
		if (i.fi != v)
		{
			build_up(i.fi, u, up);
		}
	}
}
void find_level(ll u, ll v, ll c_lvl, vll &level)
{
	level[u] = c_lvl;
	for (auto i : adj[u])
	{
		if (i.fi != v)
		{
			find_level(i.fi, u, c_lvl + 1, level);
		}
	}
}
ll find_lca(ll k1,ll k2,vll &level,vector <vll> &up)
{
	ll og_k1 = k1, og_k2 = k2;
	ll num = 0;
	if (level[k1] < level[k2])
	{
		swap(k1, k2);
	}
	ll xf = level[k1] - level[k2];
	ll ct = 0;
	vll two_factors;
	while (xf != 0)
	{
		ll temp_val = xf % 2;
		if (temp_val == 1)
			two_factors.push_back(ct);
		xf /= 2;
		ct++;
	}
	reverse(two_factors.begin(), two_factors.end());

	for (ll i = 0; i < two_factors.size(); i++)
	{
		k1 = up[k1][two_factors[i]];
		if (k1 == -1)
			break;
	}
	//o2(k1,k2);
	rrep(i, 20, 0)
	{
		if (up[k1][i] != up[k2][i] && up[k1][i] > 0 && up[k2][i] > 0)
		{
			//o4(k1, k2, up[k1][i], up[k2][i]);
			k1 = up[k1][i];
			k2 = up[k2][i];
		}
	}
	ll lca;
	if (k1 != k2)
	{
		lca = up[k1][0];
		//o1(ans);
	}
	else
	{
		lca = k1;
	}
	return lca;

}
void solve()
{
	ll n;
	i1(n);
	vector <vll> edges(n - 1, vll(3));
	rep(i, 2, n + 1)
	{
		ll k1, k2, k3;
		i3(k1, k2, k3);
		adj[k1].push_back({k2, k3});
		adj[k2].push_back({k1, k3});
		vll temp;
		edges[i - 2][0] = k1;
		edges[i - 2][1] = k2;
		edges[i - 2][2] = k3;
	}

	//o1(k);
	dfs(1, -1);
	vector <vll> up(n + 1, vll(21));
	vll level(n + 1);

	build_up(1, -1,  up);
	find_level(1, -1, 0, level);

	// rep(i, 1, n + 1)
	// {
	// 	rep(j, 0, 4)
	// 	{
	// 		cout << up[i][j] << " ";
	// 	}
	// 	cout << ln;
	// }
	vll values(n + 1);
	rep(i, 0, n - 1)
	{
		ll k1 = edges[i][0];
		ll k2 = edges[i][1];
		ll k3 = edges[i][2];
		if (parent[k1] == k2)
		{
			values[k1] += k3;
		}
		else
		{
			values[k2] += k3;
		}
	}
	//rep(i,0,n)
	// rep(i,0,timer)
	// {
	// 	cout<<st[i]<<" ";
	// }
	// cout<<ln;
	// rep(i,0,timer)
	// {
	// 	cout<<en[i]<<" ";
	// }
	// cout<<ln;
	rep(i, 1, n + 1)
	{
		//o3(st[i], en[i]+1, values[i]);
		update(1, 0, n , st[i], values[i]);
		// rep(i, 1, 4 * n)
		// {
		// 	cout << t[i] << " ";
		// }
		// cout << ln;
		update(1, 0, n , en[i], -values[i]);

		// rep(i, 1, 4 * n)
		// {
		// 	cout << t[i] << " ";
		// }
		// cout << ln;
		//o1(sum(1,0,n,0,st[i]));
	}
	// for (int i = 0; i < 8; i++)
	// {
	// 	cout << t[i] << " ";
	// }
	// cout << ln;
	ll q;
	i1(q);
	rep(i, 0, q)
	{
		ll k;
		i1(k);
		//o1(k);
		if (k == 2)
		{
			ll k1, k2;
			i2(k1, k2);
			// ll og_k1=k1,og_k2=k2;
			//o2(k1,k2);
			ll og_k1 = k1, og_k2 = k2;
			ll lca=find_lca(k1,k2,level,up);

			//o1(lca);
			ll ans = sum(1, 0, n , 0, st[og_k1]) + sum(1, 0, n , 0, st[og_k2]) - 2 * sum(1, 0, n, 0, st[lca]);
			//o3(k1, k2, lca);
			//o3(sum(1, 0, n , 0, st[og_k1]), sum(1, 0, n , 0, st[og_k2]), sum(1, 0, n, 0, st[lca]));
			o1(ans);
		}
		else
		{
			ll m1, m2;
			i2(m1, m2);
			m1--;
			ll k1 = edges[m1][0];
			ll k2 = edges[m1][1];
			ll k3 = edges[m1][2];
			if (parent[k1] == k2)
			{

				update(1, 0, n , st[k1], -values[k1] + m2);
				update(1, 0, n , en[k1] , +values[k1] - m2);
				values[k1] = m2;
			}
			else
			{

				update(1, 0, n , st[k2], -values[k2] + m2);
				update(1, 0, n , en[k2] , +values[k2] - m2);
				values[k2] = m2;
			}
			// rep(i,1,n+1)
			// {
			// 	o1(sum(1,0,n,0,st[i]));
			// }

		}


	}

}
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	ll t = 1;
	//cin >> t;

	srand(time(0));
	for (ll i = 1; i <= t; i++)
	{

		//cout << "Case #" << i << ": ";

		solve();

	}
	return 0;
}