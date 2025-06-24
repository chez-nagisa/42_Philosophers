# philosophers

`philosophers` is a concurrency project from the 42 curriculum.  
It involves simulating the Dining Philosophers Problem—a well-known synchronization problem in computer science.

The objective is to prevent race conditions and deadlocks while managing access to shared resources (forks), using threads and mutexes.

## 🧠 What I Learned

- Basics of concurrency and multithreading
- Thread management
- Mutex control and synchronization
- Techniques to avoid race conditions and deadlocks
- Time management and state synchronization design

## 🔧 How to Use

```bash
# 1. Build the project
make

# 2. Run with arguments:
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]

# Example:
./philo 5 800 200 200
```

## 📝 Arguments

1. `number_of_philosophers`: total number of philosophers (and forks)
2. `time_to_die`: time (ms) before a philosopher dies if they don't eat
3. `time_to_eat`: eating duration in ms
4. `time_to_sleep`: sleeping duration in ms
5. `[optional]`: number of times each philosopher must eat (simulation ends after that)

---

# philosophers（日本語）

`philosophers` は、42の並行処理課題の中でも**デッドロック回避とマルチスレッドの理解が問われる**プロジェクトです。  
「食事する哲学者の問題」を題材に、**共有資源（フォーク）を安全に扱いながら哲学者が食事・思考・睡眠を繰り返す**シミュレーションを作成します。

## 🧠 学んだこと

- 並行処理とマルチスレッドの基本  
- スレッド管理  
- ミューテックス制御  
- レースコンディションやデッドロックの回避手法  
- 時間管理と状態同期の設計方法

## 🔧 使い方

```bash
# 1. makeでビルド
make

# 2. 以下の形式で実行
./philo 哲学者の人数 死ぬまでの時間 食事時間 睡眠時間 [食事回数]

# 例：
./philo 5 800 200 200
```

## 📝 引数の意味

1. 哲学者の人数（＝フォークの数）  
2. `time_to_die`: 食べないと死ぬまでの時間（ミリ秒）  
3. `time_to_eat`: 食事にかかる時間（ミリ秒）  
4. `time_to_sleep`: 睡眠にかかる時間（ミリ秒）  
5. `[任意]`: 各哲学者が食事すべき回数（指定すると、全員が終えた時点で終了）

