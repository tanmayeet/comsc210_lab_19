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
  void displayReview(ReviewNode* head) {
    // First checks if the list is empty
    if (head == nullptr) {
      cout << "Empty. \n";
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
      total = total + current->rating;
      current = current->next;
    }
    if (count > 0) {
      float average = total / count;
      cout << "Average rating: " << average << "\n";
    } else {
      cout << "No reviews to average.\n";
    }
  }
};

int main() { return 0; }