// COMSC210 | Lab 19 | Tanmayee Chalamalasetti
// IDE Used: VS Code

#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Struct with review attributes
struct ReviewNode {
  float rating;
  string comment;
  ReviewNode* next;
};

class Movie {
 private:
  string title;
  ReviewNode* head;

 public:
  Movie(string t) {
    title = t;
    head = nullptr;
  }

  // addReview
  // arguments: float rating, string comment
  // returns: nothing
  void addReview(float rating, string comment) {
    ReviewNode* newNode = new ReviewNode;
    newNode->rating = rating;
    newNode->comment = comment;
    newNode->next = head;
    head = newNode;
  }

  // displayReview outputs the review
  // arguments: ReviewNode* head
  // returns: nothing
  void displayReview() {
    cout << "Movie: " << title << endl;
    // First checks if the list is empty
    if (head == nullptr) {
      cout << "No reviews. \n\n";
      return;
    }

    // then starts the review counter at 0 for
    int count = 0;
    float total = 0.0;
    cout << "Outputting all reviews:\n";

    ReviewNode* current = head;
    while (current != nullptr) {
      count++;
      cout << "   >Review #" << count << ": " << current->rating << ": "
           << current->comment << "\n";
      total += current->rating;
      current = current->next;
    }
    if (count > 0) {
      float average = total / count;
      cout << "Average rating: " << average << "\n";
    } else {
      cout << "No reviews to average.\n";
    }
  }

  void clear() {
    ReviewNode* current = head;
    while (current != nullptr) {
      ReviewNode* temp = current;
      current = current->next;
      delete temp;
    }
    head = nullptr;
  }
};

float generateRandomRating() {
  int r = rand() % 41 + 10;  // 10 to 50
  return r / 10.0;
}

int main() {
  srand(time(0));

  vector<Movie> movies;
  movies.push_back(Movie("Inception"));
  movies.push_back(Movie("The Matrix"));
  movies.push_back(Movie("Interstellar"));
  movies.push_back(Movie("The Grand Budapest Hotel"));

  ifstream infile("reviews.txt");
  if (!infile) {
    cout << "Error: Could not open reviews.txt\n";
    return 1;
  }

  string comment;
  int index = 0;

  while (getline(infile, comment)) {
    float rating = generateRandomRating();
    movies[index].addReview(rating, comment);
    index = (index + 1) % movies.size();
  }

  infile.close();

  for (int i = 0; i < movies.size(); i++) {
    movies[i].displayReview();
  }

  for (int i = 0; i < movies.size(); i++) {
    movies[i].clear();
  }

  return 0;
}