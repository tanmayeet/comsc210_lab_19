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

  // Constructor: initializes movie title and empty review list
 public:
  Movie(string t) {
    title = t;
    head = nullptr;
  }

  // addReview adds a review to the head of the linked list
  // arguments: float rating, string comment
  // returns: none
  void addReview(float rating, string comment) {
    ReviewNode* newNode = new ReviewNode;
    newNode->rating = rating;
    newNode->comment = comment;
    newNode->next = head;
    head = newNode;
  }

  // displayReview outputs the review
  // arguments: none
  // returns: none
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
    float average = total / count;
    cout << "Average rating: " << average << "\n";
  }

  // deletes all review nodes to free memory
  // arguments: none
  // returns: nothing
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

// generates a random float rating
// arguments: none
// returns: a float rating
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
    if (comment.empty()) continue;  // skip blank lines

    cout << "Adding review to movie #" << index << ": " << comment << endl;
    float rating = generateRandomRating();
    movies[index].addReview(rating, comment);
    index = (index + 1) % movies.size();
  }

  infile.close();

  // Displays reviews for each movie
  for (int i = 0; i < movies.size(); i++) {
    movies[i].displayReview();
  }

  // Cleans up memory
  for (int i = 0; i < movies.size(); i++) {
    movies[i].clear();
  }

  return 0;
}