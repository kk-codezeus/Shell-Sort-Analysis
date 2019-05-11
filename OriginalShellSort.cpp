#include<bits/stdc++.h>
using namespace std;
using namespace chrono;

uniform_int_distribution<int> uniformDistribution(INT_MIN,INT_MAX);

class OriginalShellSort
{
    private:
        random_device seed;
        void Swap(int *a,int *b)
        {
            int temp = *a;
            *a = *b;
            *b = temp;
        }
    public:
        vector<int> unifDistPerm;
        vector<int> almostSortedPerm;
        OriginalShellSequence()
        {
            srand(time(0));
        }
        void fyShuffle(vector<int> &dist)
        {
            int n = dist.size();
            for(int i = n - 1;i > 0;i--)
            {
                int j = rand() % (i + 1);
                Swap(&dist[i],&dist[j]);
            }
        }
        void shuffle(int n)
        {
            for(int i = 0;i < 2*log2(double(n));i++)
            {
                int e1 = rand() % n;
                int e2 = rand() % n;
                Swap(&almostSortedPerm[e1],&almostSortedPerm[e2]);
            }
        }
        void generateUnifDist(int n)
        {
            unifDistPerm.clear();
            for(int i = 0;i < n;i++)
                unifDistPerm.push_back(uniformDistribution(seed));
        }
        void generateAlmSortPerm(int n)
        {
            almostSortedPerm.clear();
            for(int i = 1;i <= n;i++)
                almostSortedPerm.push_back(i);
            shuffle(n);
        }
        void printSequence(vector<int> &dist)
        {
            for(int i = 0;i < dist.size();i++)
                cout<<dist[i]<<" ";
            cout<<endl;
        }
        void shellSort(vector<int> &dist)
        {
            int n = dist.size();
            for (int gap = n / 2; gap > 0; gap /= 2)
            {
                for (int i = gap; i < n; i++)
                {
                    int temp = dist[i];
                    int j = i;
                    while (j >= gap && temp < dist[j - gap])
                    {
                        dist[j] = dist[j - gap];
                        j -= gap;
                    }
                    dist[j] = temp;
                }
            }
        }
};

int main()
{
    OriginalShellSort sequence;
    vector<double> unifDistTimes;
    vector<double> almSortTimes;

    // Uniform distribution time calculation
    for(int n = 10;n <= 1000000;n *= 10)
    {
        sequence.generateUnifDist(n);

        steady_clock::time_point t1,t2;
        int64_t total_duration = 0;

        for(int i = 0;i < 10;i++)
        {
            t1 = steady_clock::now();

            sequence.shellSort(sequence.unifDistPerm);

            t2 = steady_clock::now();
            auto duration = duration_cast<nanoseconds>((t2 - t1));
            total_duration += int64_t(duration.count());

            sequence.fyShuffle(sequence.unifDistPerm);
        }
        double averageTime = double(total_duration) / 10;
        unifDistTimes.push_back(averageTime);
    }
    cout<<fixed<<setprecision(2);
    cout<<"For uniform distribution sequences\n";
    int n = 10;
    for(int i = 0;i < unifDistTimes.size();i++)
    {
        cout<<n<<": ";
        cout<<unifDistTimes[i]<<endl;
        n *= 10;
    }

    cout<<endl<<endl;

    // Almost sorted sequence
    for(int n = 10;n <= 1000000;n *= 10)
    {
        sequence.generateAlmSortPerm(n);

        steady_clock::time_point t1,t2;
        int64_t total_duration = 0;

        for(int i = 0;i < 10;i++)
        {
            t1 = steady_clock::now();

            sequence.shellSort(sequence.almostSortedPerm);

            t2 = steady_clock::now();
            auto duration = duration_cast<nanoseconds>((t2 - t1));
            total_duration += int64_t(duration.count());

            sequence.shuffle(n);
        }
        double averageTime = double(total_duration) / 10;
        almSortTimes.push_back(averageTime);
    }
    n = 10;
    cout<<"For almost sorted sequences\n";
    for(int i = 0;i < almSortTimes.size();i++)
    {
        cout<<n<<": ";
        cout<<almSortTimes[i]<<endl;
        n *= 10;
    }
    return 0;
}
