void zero(int cost, int weight) {
    for (int i = V; i >= cost; i--) {
        if (dp[i - cost] + weight > dp[i]) {
            dp[i] = max(dp[i], dp[i - cost] + weight);
        }
    }
}

void complete(int cost, int weight) {
    for (int i = cost; i <= V; i++) {
        dp[i] = max(dp[i], dp[i - cost] + weight);
    }
}

void multi(int cost, int amount, int weight) {
    if (cost * amount >= V) {
        complete(cost, weight);
        return;
    }
    int k = 1;
    while (k < amount) {
        zero(k * cost, k * weight);
        amount -= k;
        k *= 2;
    }
    zero(amount * cost, amount * weight);
}