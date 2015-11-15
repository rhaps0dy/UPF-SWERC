// guardar todos los primos entre 2 y 10010 en v
int k = 0, v[10000];
v[k++] = 2; 
for (int i = 3; i <= 10010; i += 2) {
    bool b = true;
    for (int j = 0; b && v[j]*v[j] <= i; j++)
        b = i%v[j] > 0;
    if (b) v[k++] = i;
}
  
// probar si un numero x <= 100000000 es primo
int x;
cin >> x;
bool primo = true;
for (int j = 0; primo && v[j]*v[j] <= x; j++)
    primo = x%v[j] > 0;
