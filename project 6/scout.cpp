 /**
    * Creates a random array of integers 0-9 and queries the
    * user for one such integer; the program searches the array
    * and reports if the user’s integer is found.
    * @file scout.cpp
    * @author(s) Derya Arikan
    * @date April 5, 2023
    */

#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

/// @brief Given a vector of integers, finds the largest number within it.
/// @param A Vector of integers
/// @return Integer value of the largest element in A
int max(vector<int> A) {
  int current_max = 0;
  for (int i; i < A.size(); i++) {
    if (A[i] > current_max) {
      current_max = A[i];
    }
  }
  return current_max;
}

/// @brief Determines whether a given vector is a set.
/// @param A Vector of integers
/// @return true if it is a set, false if it is not. 
bool is_set(vector<int> A) {
  if (A.front() == A.back()) {
    return true;
  }
  return false;
}

/// @brief Determines whether a given vector is a run.
/// @param A Vector of integers
/// @return true if it is a run, false if it is not.
bool is_run(vector<int> A) {
  if (A.front() == A.back()) {
    return false;
  }
  return true;
}

/// @brief Given a vector of integers, the first and last index of its desired subvector,
///        extracts and returns the subvector
/// @param v Vector of integers
/// @param i The beginning of the subvector
/// @param j The end of the subvector
/// @return The subvector of v
vector<int> subvector(vector<int> v, int i, int j) {
  vector<int> new_vector = {};
  for (int n = i; n <= j; n++) {
    new_vector.push_back(v[n]);
  }
  return new_vector;
}

/// @brief Operator overload for determining whether the LHS set (or run) is more
///        powerful than the RHS vector
/// @param A LHS vector
/// @param B RHS vector
/// @return boolean value: true if A > B, false if A <= B 
bool operator>(vector<int> A, vector<int> B) {
  // first compare size
  if (A.size() > B.size()) {
    return true;
  }
  if (B.size() > A.size()) {
    return false;
  }
  // if both have the same size, choose run over set
  if (is_set(A) && is_run(B)) {
    return true;
  }
  if (is_set(B) && is_run(A)) {
    return false;
  }
  // if both have the same type, choose whichever has the highest value
  if (max(A) > max(B)) {
    return true;
  }
  if (max(B) > max(A)) {
    return false;
  }
  // if none of the conditions were met, they are equal!
  return false;
}

/// @brief Operator overload for determining whether two sets (or runs) are equally
///        powerful
/// @param A LHS vector
/// @param B RHS vector
/// @return boolean value: true if A == B, false if A != B
bool operator==(vector<int> A, vector<int> B) {
  // first compare size
  if (A.size() > B.size()) {
    return false;
  }
  if (B.size() > A.size()) {
    return false;
  }
  // if both have the same size, check whether they are the same type
  if (is_set(A) && is_run(B)) {
    return false;
  }
  if (is_set(B) && is_run(A)) {
    return false;
  }

  // if both have the same type, check if they have the same values
  if (max(A) > max(B)) {
    return false;
  }
  if (max(B) > max(A)) {
    return false;
  }
  // if none of the conditions were met, they are equal!
  return true;
}

/// @brief Operator overload for cout-ing vectors. 
/// @param output Output stream output
/// @param vec Vector that will be cout-ed
/// @return output
ostream &operator<<(ostream &output, vector<int> vec) {
  for (int i = 0; i < vec.size(); i++) {
    if (i != vec.size()-1) { 
    output << vec[i] << ' ';
    } else {
      output << vec[i];
    }
  }
  return output;
}

/// @brief Holds the starting cards, its size, and methods to find the best insertion point
///        for a card given its value. 
class Hand {
private:
  vector<int> cards;
  int size = 0;

public:
  vector<vector<int>> all_hands;
  void hand_size(int n);
  int get_size();
  void add(int n);
  void display_cards();
  vector<vector<int>> generate_possible_hands(int n);
  vector<int> best_run_or_set(vector<int> h, int h_size);
  vector<int> compare_all_hands();
};

/// @brief Used to input the size of the starting hand of cards.
/// @param n Integer size of the vector cards
void Hand::hand_size(int n) { 
    size = n; 
}

/// @brief The size of the starting hand of cards. 
/// @return Integer size of the vector cards in a Hand object
int Hand::get_size() { 
    return size; 
}

/// @brief Used to add to the private variable cards in a Hand object.
/// @param n The card that will be added. 
void Hand::add(int n) { 
    cards.push_back(n);
}

/// @brief Given a new card to be inserted within a hand, generates a 2D vector
///        that holds all possible hands. It is organized such that the 0th vector
///         has the new card inserted into 0th index, 1st vector has it in the 1st index,
///         and such. 
/// @param n The value of the new card that is to be inserted. 
/// @return Vector of vectors that each hold a possible hand.
vector<vector<int>> Hand::generate_possible_hands(int n) {
  vector<vector<int>> possible_hands = {};
  for (int i = 0; i <= size; i++) {
    possible_hands.push_back(cards);
    if (i == size) {
      possible_hands[i].push_back(n);
    } else {
      possible_hands[i].insert(possible_hands[i].begin() + i, n);
    }
  }
  return possible_hands;
}

/// @brief Given a hand, finds the best run or set within it.
/// @param h vector<int> that holds a hand of cards.
/// @param s integer size of the vector h
/// @return vector<int> of the best run or set found within the hand
vector<int> Hand::best_run_or_set(vector<int> h, int s) {   
  vector<int> current_best = {0};                           
  for (int i = 0; i < s; i++) {
    int j = i;
    if (h[i] == h[j + 1]) {
      while (h[i] == h[j + 1]) { // look for set
        j++;
      }
    } else if (h[i] == h[j + 1] + 1) {
      while (h[j] == h[j + 1] + 1) { // look for decreasing run
        j++;
      }
    } else if (h[i] == h[j + 1] - 1) {
      while (h[j] == h[j + 1] - 1) { // look for increasing run
        j++;
      }
    }
    if (i != j) {
      vector<int> candidate_best = subvector(h, i, j);
      if (candidate_best > current_best) {
        current_best = candidate_best;
      }
    }
  }
  return current_best;
}

/// @brief Compares all the possible hands in the 2D vector all_hands
/// @return A vector containing the indices of the best hands in all_hands
///         See the notes for generate_possible_hands() for explanation why
///         these indices correspond to the index into which the new card is 
///         being inserted.
vector<int> Hand::compare_all_hands() {
  vector<int> index = {0}; // stores indices of most powerful hands
  vector<int> current_best_run = best_run_or_set(all_hands[0], size + 1);
  for (int i = 1; i < all_hands.size(); i++) {
    vector<int> candidate_best_run = best_run_or_set(all_hands[i], size + 1);
    if (current_best_run == candidate_best_run) {
      index.push_back(i);
    } else if (current_best_run > candidate_best_run) {
      // do nothing
    } else {
      current_best_run = candidate_best_run;
      index = {i};
    }
  }
  return index;
}

/// @brief Enables testing from file with commands defined in this
///        function.
/// @param file_name Name of the file that contains the test
///        commands.
void test_from_file(string file_name) {
  ifstream the_file(file_name);

  if (!the_file.is_open()) {
    cout << "File not found: " << file_name << endl;
    throw invalid_argument("File not found: " + file_name);
  }

  Hand h;
  string command;
  int item;

  while (the_file >> command) {

    if (command == "hand_size") {
      the_file >> item;
      h.hand_size(item);
    } else if (command == "hand") {
      for (int i = 0; i < h.get_size(); i++) {
        the_file >> item;
        h.add(item);
      }
    } else if (command == "insert") {
      the_file >> item;
      h.all_hands = h.generate_possible_hands(item);
      cout << h.compare_all_hands() << endl;
    } else {
      cout << "ERROR: Incorrect command: " << command << endl;
    }
  }
}

/// @brief Controls program flow.
/// @param argc Argument count
/// @param argv Argument vector
int main(int argc, char **argv) {
  if (argc != 2) {
    cout << "usage: " << argv[0] << " <commands file name>" << endl;
    exit(1);
  }

  string test_file = argv[1];
  test_from_file(test_file);
}