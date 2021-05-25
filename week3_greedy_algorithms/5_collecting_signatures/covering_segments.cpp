#include <algorithm>
#include <iostream>
#include <climits>
#include <vector>
#include <cassert>
#include <algorithm>
#include <iterator>

using std::vector;

struct Segment {
  int start, end;
};

vector<int> optimal_points(vector<Segment> &segments) {
  vector<int> points;
  //write your code here
  std::vector<Segment> segments_copy;
  std::copy(segments.begin(), segments.end(), back_inserter(segments_copy));

  // Sort segment in increasing order
  // Get first element
  std::vector<int> first_element;
  for (auto it:segments_copy)
  {
    first_element.push_back(it.start);
  }
  std::sort(first_element.begin(),first_element.end());
  std::vector<Segment> segments_copy_copy;
  std::copy(segments.begin(), segments.end(), back_inserter(segments_copy_copy));
  for (int i = 0; i < segments_copy.size();i++)
  {
    for (int j = 0; j < segments_copy_copy.size(); j++)
    {
      if (first_element[i] == segments_copy_copy[j].start)
      {
        segments_copy[i] = segments_copy_copy[j];
        segments_copy_copy[j].start = -1;
        break;
      }
    }
  }
  // Sort again base on end value
  segments_copy_copy.clear();
  std::copy(segments_copy.begin(), segments_copy.end(), back_inserter(segments_copy_copy));
  for (int i = 0; i < segments_copy_copy.size()-1;i++)
  {
    if (segments_copy_copy[i].start == segments_copy_copy[i+1].start)
    {
      if (segments_copy_copy[i].end > segments_copy_copy[i+1].end)
      {
        std::swap(segments_copy[i],segments_copy[i+1]);
      }
    }
  }

  // Print out range
  std::vector<std::vector<int>> all_vec;
  for (auto it:segments_copy)
  {
    std::vector<int> temp_vec;
    int start = it.start;
    int end = it.end;
    // std::cout << "Vec Start" << std::endl;
    for (int i=start;i<=end;i++)
    {
      temp_vec.push_back(i);
      // std::cout << " " << i;
    }
    // std::cout << "\nVec end" << std::endl;
    all_vec.push_back(temp_vec);
  }

  std::vector<int> v_intersection;
  
  bool is_matched = false; 
  for (int i=0;i<all_vec.size()-1;i++)
  {
    is_matched =false;
    std::vector<int> v1 = all_vec[i]; 
    std::vector<int> v2 = all_vec[i+1]; 
    // std::cout << "i: " << i << std::endl;
    if (!v_intersection.empty())
    {
      for (int j=v_intersection.size()-1;j>=0;j--)
      {
        for (int k=v2.size()-1;k>=0;k--)
        {
          // std::cout << "Vintersection: " << v_intersection[j] << std::endl;
          // std::cout << "V2: " << v2[k] << std::endl;
          if (v2[k] == v_intersection[j])
          {
            is_matched = true;
            // std::cout << "Matched!!!" << std::endl;
            break;
          } 
        }
        if (is_matched) break;
      }
    }
    
    if (is_matched) 
    {
      is_matched = false;
      // std::cout << "Matched!!! indice: "<< i << " Size: " << all_vec.size()-1 << std::endl;
      continue;
    }
    for (int j=v1.size()-1;j>=0;j--)
    {
      for (int k=v2.size()-1;k>=0;k--)
      {
        // std::cout << "V1: " << v1[j] << std::endl;
        // std::cout << "V2: " << v2[k] << std::endl;
        if (v2[k] == v1[j])
        {

          v_intersection.push_back(v2[k]);
          is_matched = true;
          break;
        }
      }
      if (is_matched) break;
    }
    // Disjointed
    if (!is_matched) 
    {
      v_intersection.push_back(v2[v2.size()-1]);

      // check v1 has any match
      std::vector<int> v1_temp_check = v1;
      bool this_check=false;
      for (auto v1it:v1_temp_check)
      {
        for (int v1in=0;v1in<v_intersection.size();v1in++)
        {
          if (v1it == v_intersection[v1in])
          {
            this_check = true;
            break;
          }
        }
        if (this_check) break;
      }
      if (!this_check)
      {
        v_intersection.push_back(v1_temp_check[v1_temp_check.size()-1]);
      }
    }
  }
  std::sort(v_intersection.begin(),v_intersection.end());



  // Check all vector
  // For reduction of points
  std::vector<int> to_remove;
  for (int i = 0;i<all_vec.size();i++)
  {
    std::vector<int> current_vec = all_vec[i];
    // If more than less than 2 point defo no
    if (current_vec.size() < 2) continue;
    int num_points=0,last_point=0;
    for (auto it:current_vec)
    {
      for (auto itt:v_intersection)
      {
        if (it==itt)
        {
          num_points+=1;
          last_point=it;
        }
      }
    }
    if (num_points < 2) continue;

    // std::cout << "last point: " << last_point << " num of points " << num_points << std::endl;
    //Compare next vector to last point
    int update_i=i+1;
    if (update_i< all_vec.size())
    {
      std::vector<int> next_vec = all_vec[update_i];
      while (true)
      {
        if (next_vec.size()<2)
        {
          update_i+=1;
          if (update_i< all_vec.size())
          {
            next_vec = all_vec[update_i];
            // last_point=current_vec[current_vec.size()-1];
            //  std::cout << "updated last point: " << last_point << std::endl;
          }
          else
            break;
        }
        else 
          break;
      }
      if (next_vec.size() < 2) continue;
      
      // std::cout << "next_vec size: " << next_vec.size() << std::endl;
      num_points=0;
      bool exit_for=false;
      for (auto end_vec_ind=next_vec.size()-1; end_vec_ind>=0;end_vec_ind--)
      {
        int it = next_vec[end_vec_ind];
        // std::cout << "it: " << it << std::endl;
        //for (auto itt:v_intersection)
        for (int end_inter=v_intersection.size()-1; end_inter>=0;end_inter--)
        {
          int itt = v_intersection[end_inter];
          // std::cout << "itt: " << itt << std::endl;
          if (it==itt)
          {
            // std::cout << "last  itt: " << itt << std::endl;
            // std::cout << "last  itt last_point: " << last_point << std::endl;
            if (itt == last_point)
            {
              // Cannot remove
            }
            else
            { 
              // Remove last point
              to_remove.push_back(last_point);
            }
            exit_for=true;
            break;
          }
        }
        if (exit_for) break;
      }
    }
  }
  // std::cout << "to_remove size: " << to_remove.size() << std::endl;
  for(auto &it:to_remove)
  {
    // std::cout << "to_remove it: " << it << std::endl;
    for(auto itt:all_vec)
    {
      if (itt.size()==1 && it == itt[0])
        it=-1;
    }
  }

  for (auto it:to_remove)
  {
    for(int i=0;i<v_intersection.size();i++)
    {
      if(it == v_intersection[i])
        v_intersection[i] = -1;
    }
  }

  std::vector<int> temp_v_inter = v_intersection;
  v_intersection.clear();
  for (int i = 0;i<temp_v_inter.size();i++)
  {
    if (temp_v_inter[i]== -1) continue;
    v_intersection.push_back(temp_v_inter[i]);
  }

    // Check which segment missing
  for(auto it:all_vec)
  {// each vector
    bool is_check=false;
    for (auto itt:it)
    {//Check ele inside vector
      for (auto checkit:v_intersection)
      {
        if (itt == checkit)
        {
          is_check=true;
          break;
        }
      }
      if (is_check) break;
    }
    if (!is_check) v_intersection.push_back(it[it.size()-1]);
  }

  std::sort(v_intersection.begin(),v_intersection.end());

  // std::cout << "v_intersection size: " << v_intersection.size() << std::endl;
  points = v_intersection;



  // std::cout << "Vec Start Final" << std::endl;
  // for (auto it:points)
  // {
  //   std::cout << it << " ";
  // }
  // std::cout << "\nVec end Final" << std::endl;

  return points;
}
void test_solution()
{
  std::vector<Segment> vec_seg = {{1,3},{2,5},{3,6}};
  std::vector<int> answer = {3};
  assert(optimal_points(vec_seg)==answer);
  vec_seg = {{4,7},{1,3},{2,5},{5,6}};
  answer = {3,5};
  assert(optimal_points(vec_seg)==answer);
  vec_seg = {{4,7},{1,3},{2,5},{5,6}, {0, 1},{1, 1}};
  answer = {1,5};
  assert(optimal_points(vec_seg)==answer);
  
  vec_seg = {{0,1},{5,6}};
  answer = {1,6};
  assert(optimal_points(vec_seg)==answer);

  
  vec_seg = {{0,1},{1,1},{1,2},{1,3},{2,4},{2,4},{3,4},{4,4},{5,5}};
  answer = {1,4,5};
  assert(optimal_points(vec_seg)==answer);

  vec_seg = {{10,10}, {10,12},{12,14},{12,14},{14,16},{15,15},{17,18},{17,19}};
  answer = {10,14,15,18};
  assert(optimal_points(vec_seg)==answer);

  vec_seg = {{23,23}, {25,27},{26,26},{26,28},{28,28},{29,29}};
  answer = {23,26,28,29};
  assert(optimal_points(vec_seg)==answer);

  vec_seg = {{79,79},{79,81},{80,82},{81,81},{81,82},{82,84},{83,84},{83,84},{83,84},{84,85},{86,87}};
  answer = {79,81,84,87};
  assert(optimal_points(vec_seg)==answer);
}

int main() {
  int n;
  std::cin >> n;
  vector<Segment> segments(n);
  for (size_t i = 0; i < segments.size(); ++i) {
    std::cin >> segments[i].start >> segments[i].end;
  }
  vector<int> points = optimal_points(segments);
  std::cout << points.size() << "\n";
  for (size_t i = 0; i < points.size(); ++i) {
    std::cout << points[i] << " ";
  }
  // test_solution();
}
