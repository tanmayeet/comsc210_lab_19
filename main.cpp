// COMSC210 | Lab 19 | Tanmayee Chalamalasetti
// IDE Used: VS Code

#include <fstream>
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

  void addReview(float rating, string comment) {}
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

}

int main() {
  int choice;  // choice for head or tail
  cout << "Which linked list method should we use?\n";
  cout << "   [1] New nodes are added at the head of the linked list\n";
  cout << "   [2] New nodes are added at the tail of the linked list\n";
  cout << "   Choice: ";
  cin >> choice;

  // input validation if someone puts in another value other than 1 or 2
  while (choice != 1 && choice != 2) {
    cout << "ERROR: Please enter 1 or 2.\nChoice: ";
    cin >> choice;
  }

  // sets true to 1
  bool addToHead = (choice == 1);

  // sets head and tail to null pointers
  ReviewNode* head = nullptr;
  ReviewNode* tail = nullptr;

  // initialized some variables for input validation and checking for more
  // reviews
  char multiple = 'y';
  float rating;
  string comment;

  while (multiple == 'y' || multiple == 'Y') {
    cout << "Enter review rating 0-5: ";
    cin >> rating;
    while (rating > max_rating || rating < min_rating) {
      cout << "ERROR: Rating must be between 0.0 and 5.0. Try again: ";
      cin >> rating;
    }
    cout << "Enter review comments: ";
    cin >> comment;

    // created a new Node
    ReviewNode* newNode = new ReviewNode;
    newNode->rating = rating;
    newNode->comment = comment;
    newNode->next = nullptr;

    // checks if addToHead is true or 1 and adds to the head
    if (addToHead == true) {
      newNode->next = head;
      head = newNode;
      if (tail == nullptr) {
        tail = newNode;
      }
      // else (if it is 2) it adds to the tail
    } else {
      if (head == nullptr) {
        head = newNode;
        tail = newNode;
      } else {
        tail->next = newNode;
        tail = newNode;
      }
    }

    cout << "Enter another review? Y/N: ";
    cin >> multiple;
    cin.ignore();

    // I put both lower case and upper case Y
    while (multiple != 'y' && multiple != 'Y' && multiple != 'n' &&
           multiple != 'N') {
      cout << "ERROR: Please enter Y or N: \n";
      cin >> multiple;
      cin.ignore();
    }
  }

  // call displayReview to display the review
  displayReview(head);

  // deleting nodes
  ReviewNode* current = head;
  while (current != nullptr) {
    ReviewNode* temp = current;
    current = current->next;
    delete temp;
  }

  return 0;
}