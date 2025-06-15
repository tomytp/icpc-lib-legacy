
// Perfomance geral (seguro p/ CP)
 #pragma GCC optimize("O3,unroll-loops,fast-math")
 #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
 
// Máximo vetor + FP agressivo (pode quebrar precisão)
 #pragma GCC optimize("Ofast,fast-math,unroll-loops,inline")
 #pragma GCC target("avx2,fma,sse4.2,popcnt,tune=native")

// Foco em binário pequeno
 #pragma GCC optimize("Os")
