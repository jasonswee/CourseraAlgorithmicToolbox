#include <iostream>
#include <vector>
#include <cassert>

//Sort
#include <algorithm>
// Power
#include <cmath>
// Rand 
#include <stdlib.h>
// Time 
#include <chrono>
//pair
#include <utility>

using std::vector;

int max_end_g;
const int g_start = -1, g_point = 0, g_end = 1;

// Driver function to sort the vector elements
// by second element of pairs
bool sortbysec(const std::pair<int,int> &a,
              const std::pair<int,int> &b)
{
    return (a.second < b.second);
}
int random_func(int low, int high)
{
  return rand() % high + low;
}

void print_this(vector<int> input)
{
  for (auto i:input)
  {
    std::cout << i;
  }
  std::cout << std::endl;
}
void print_this(vector<vector<int>> input)
{
  for (auto i:input)
  {
    std::cout << i[0] << ' ' << i[1] << std::endl;
  }
  std::cout << std::endl;
}
vector<int> fast_count_segments(vector<vector<int>> segs_vec, vector<vector<int>> points) 
{
  vector<int> cnt(points.size());
  std::sort(points.begin(),points.end());
  
  int current_seg_index=0;
  for (size_t i = 0; i < points.size(); i++) 
  {
    for (size_t j = current_seg_index; j < segs_vec.size(); j++) 
    {
      // cnt[points[i][1]] += segs_vec[j][0] <= points[i][0] && points[i][0] <= segs_vec[j][1];
      // If the current g_point is bellow current segment start leave
      if (points[i][0] < segs_vec[j][0]) break;
      cnt[points[i][1]] += segs_vec[j][0] <= points[i][0] && points[i][0] <= segs_vec[j][1];
    }
  }

  return cnt;
}
vector<int> fast_count_segments_ver2(vector<vector<int>> segs_vec, vector<vector<int>> points) 
{
  vector<int> cnt(points.size());
  
  int current_seg_index=0;
  // for (size_t i = 0; i < points.size(); i++) 
  for (size_t i = 0; i < points.size() && points[i][0] < max_end_g; i++) 
  {
    for (size_t j = current_seg_index; j < segs_vec.size(); j++) 
    {
      // cnt[points[i][1]] += segs_vec[j][0] <= points[i][0] && points[i][0] <= segs_vec[j][1];
      // If the current g_point is bellow current segment start leave
      if (points[i][0] < segs_vec[j][0]) break;
      cnt[points[i][1]] += points[i][0] <= segs_vec[j][1];
    }
  }

  return cnt;
}
vector<int> fast_count_segments_ver3(vector<vector<int>> segs_vec, vector<vector<int>> points) 
{
  vector<int> cnt(points.size());
  int in_segment = 0, point_ind = 0;
  for (int i = 0; i < segs_vec.size(); i++) 
  {
    if (segs_vec[i][1] == g_start)
    {
      in_segment++;
      // std::cout << " segment current value: " << segs_vec[i][0];
      // std::cout << " + segment current: " << in_segment << std::endl;
    }
    else if (segs_vec[i][1] == g_end)
    {
      in_segment--;
      // std::cout << " segment current value: " << segs_vec[i][0];
      // std::cout << " - segment current: " << in_segment << std::endl;
    }
    else if (segs_vec[i][1] == g_point)
    {
      cnt[points[point_ind][1]] = in_segment;
      // std::cout << " + point ind current: " << point_ind << std::endl;
      // std::cout << "Sending to cnt index: (points[point_ind][1])  " << points[point_ind][1] << std::endl;
      // std::cout << " saved in_segment: " << in_segment << std::endl;
      // std::cout << "Print current CNT: " << std::endl;
      point_ind++;
      if (point_ind >= points.size()) break; 
      
    }
  }
  return cnt;
} 

vector<int> naive_count_segments(vector<vector<int>> segs_vec, vector<vector<int>> points) {
  vector<int> cnt(points.size());
  std::sort(segs_vec.begin(),segs_vec.end());
  for (size_t i = 0; i < points.size(); i++) {
    for (size_t j = 0; j < segs_vec.size(); j++) {
      cnt[i] += segs_vec[j][0] <= points[i][0] && points[i][0] <= segs_vec[j][1];
    }
  }
  return cnt;
}
void test_rand()
{
  // number of segments
  // int s = random_func(1, 50000);
  int s = 1*pow(10,6); 
  // number of points
  int p = random_func(1, 50000);

  vector<vector<int>> points, points_sorted;
  vector<vector<int>> segs_vec;
  vector<vector<int>> segs_vec_v3;

  int a,b,point;
  for (int i = 0; i < s; i++)
  {
      a = random_func(-pow(10, 8), pow(10, 8));
      b = random_func(a, pow(10, 8));
      segs_vec.push_back({a,b});
      segs_vec_v3.push_back({a,g_start});
      segs_vec_v3.push_back({b,g_end});
  }
  for (int i = 0; i < p; i++)
  {
    point = random_func(-pow(10, 8), pow(10, 8));
    points.push_back({point, i});
    segs_vec_v3.push_back({point,g_point});
  }
  points_sorted = points;
  std::sort(points_sorted.begin(),points_sorted.end());
  std::sort(segs_vec.begin(),segs_vec.end());
  std::sort(segs_vec_v3.begin(),segs_vec_v3.end());

  auto start = std::chrono::high_resolution_clock::now();
  vector<int> ans_naive = naive_count_segments(segs_vec, points);
  auto stop = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::duration<double>>(stop - start);
  std::cout << "Naive Time taken: " << duration.count() << " seconds" << std::endl;

  
  start = std::chrono::high_resolution_clock::now();
  vector<int> ans_fast = fast_count_segments(segs_vec, points_sorted);
  stop = std::chrono::high_resolution_clock::now();
  duration = std::chrono::duration_cast<std::chrono::duration<double>>(stop - start);
  std::cout << "Fast Time taken: " << duration.count() << " seconds" << std::endl;


  max_end_g = -pow(10, 8)-1;
  for (auto i: segs_vec)
  {
    if (i[1] > max_end_g) max_end_g=i[1];
  }

  start = std::chrono::high_resolution_clock::now();
  vector<int> ans_fast_ver2 = fast_count_segments_ver2(segs_vec, points_sorted);
  stop = std::chrono::high_resolution_clock::now();
  duration = std::chrono::duration_cast<std::chrono::duration<double>>(stop - start);
  std::cout << "Fast 2 Time taken: " << duration.count() << " seconds" << std::endl;



  start = std::chrono::high_resolution_clock::now();
  vector<int> ans_fast_ver3 = fast_count_segments_ver3(segs_vec_v3, points_sorted);
  stop = std::chrono::high_resolution_clock::now();
  duration = std::chrono::duration_cast<std::chrono::duration<double>>(stop - start);
  std::cout << "Fast 3 Time taken: " << duration.count() << " seconds" << std::endl;

  assert(ans_fast==ans_naive);
  assert(ans_fast_ver2==ans_fast);
  assert(ans_fast_ver3==ans_fast_ver2);
}
void test_solution()
{
  vector<vector<int>> points = {{1,0}, {6,1}, {11,2}}, points_sorted;
  vector<vector<int>> segs_vec = {{0,5},{7,10}};
  vector<vector<int>> segs_vec_v3;
  vector<int> cnt;
  assert(naive_count_segments(segs_vec, points) == fast_count_segments(segs_vec, points));

  segs_vec = {{-10,10}};
  points = {{-100,0}, {100,1}, {0,2}};
  points_sorted = points;
  segs_vec_v3 = {{-10,g_start},{10, g_end}, {-100,g_point}, {100,g_point}, {0,g_point}};
  std::sort(segs_vec_v3.begin(),segs_vec_v3.end());
  std::sort(points_sorted.begin(),points_sorted.end());
  assert(naive_count_segments(segs_vec, points) == fast_count_segments(segs_vec, points_sorted));
  assert(naive_count_segments(segs_vec, points) == fast_count_segments_ver3(segs_vec_v3, points_sorted));

  segs_vec = {{0,5},{-3,2},{7,10}};
  points = {{1,0}, {6,1}};
  points_sorted = points;
  segs_vec_v3 = {{0,g_start},{-3,g_start},{7,g_start},{5,g_end},{2, g_end},{10, g_end}, {1,g_point}, {6,g_point}};
  std::sort(segs_vec_v3.begin(),segs_vec_v3.end());
  std::sort(points_sorted.begin(),points_sorted.end());
  assert(naive_count_segments(segs_vec, points) == fast_count_segments(segs_vec, points_sorted));
  assert(naive_count_segments(segs_vec, points) == fast_count_segments_ver3(segs_vec_v3, points_sorted));
}
int main() 
{
  // int n, m;
  // std::cin >> n >> m;
  // vector<int> starts(n), ends(n);
  // vector<vector<int>> segs_vec(n);

  // max_end_g = -pow(10, 8)-1;

  // for (size_t i = 0; i < starts.size(); i++) {
  //   std::cin >> starts[i] >> ends[i];
  //   segs_vec[i] = {starts[i],ends[i]};

  //   if (ends[i] > max_end_g) max_end_g=ends[i];
  //   // segs_vec.push_back({i,starts[i]});
  // }
  // std::sort(segs_vec.begin(),segs_vec.end());

  // vector<vector<int>> points(m);
  // int value;
  // for (size_t i = 0; i < points.size(); i++) {
  //   std::cin >> value;
  //   points[i]={value,(int)i};
  // }
  // //use fast_count_segments
  // // vector<int> cnt = naive_count_segments(segs_vec, points);
  // vector<int> cnt = fast_count_segments_ver2(segs_vec, points);
  // for (size_t i = 0; i < cnt.size(); i++) {
  //   std::cout << cnt[i] << ' ';
  // }


  int n, m;
  std::cin >> n >> m;
  vector<int> starts(n), ends(n);
  vector<vector<int>> segs_vec;

  for (size_t i = 0; i < n; i++) 
  {
    std::cin >> starts[i] >> ends[i];
    segs_vec.push_back({starts[i], g_start});
    segs_vec.push_back({ends[i], g_end});
  }

  vector<vector<int>> points;
  int point;
  for (int i = 0; i < m; i++) 
  {
    std::cin >> point;
    points.push_back({point,i});
    segs_vec.push_back({point, g_point});
  }
  //use fast_count_segments
  // vector<int> cnt = naive_count_segments(segs_vec, points);
  std::sort(segs_vec.begin(),segs_vec.end());
  std::sort(points.begin(),points.end());
  vector<int> cnt = fast_count_segments_ver3(segs_vec, points);
  for (size_t i = 0; i < cnt.size(); i++) {
    std::cout << cnt[i] << ' ';
  }

  // test_solution();
  // test_rand();  
}
