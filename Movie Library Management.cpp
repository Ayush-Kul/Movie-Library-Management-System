#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

class Media 
{  // Base class
protected:
    string title;
    string format;
public:
    Media() 
    {
    }
    Media(string t, string f) : Media() 
    {
    title = t;
    format = f;
   }

    string getTitle() const 
    { 
        return title; 
    }
    string getFormat() const 
    {
         return format; 
    }

    void setTitle(string t) 
    { 
        title = t; 
    }
    void setFormat(string f) 
    { 
        format = f;
         }
    virtual void display() 
    {
        cout << title << " [" << format << "]";
    }
};

class Movie : public Media {  // Derived class
private:
    string director;
public:
    Movie() 
    {
    }
    Movie(const string& t, const string& d, const string& f)
    {
    title = t;
    format = f;
    director = d;
    }

    string getDirector() const 
    { 
        return director; 
        }

    void setDirector(string d) 
    { 
        director = d; 
        }

    bool operator<(const Movie& other) const 
    {
        return title < other.title;
    }
     void display() 
      {
        cout << title << " (" << director << ") [" << format << "]";
    }
};

class Library {
private:
    vector<Movie> movies;
public:
    void addMovie(Movie m) 
    {
        movies.push_back(m);
        sort(movies.begin(), movies.end());
    }
void removeMovie(string title) 
{
    bool movieFound = false;
    for (auto it = movies.begin(); it != movies.end(); ++it)
    {
        if (it->getTitle() == title) {
            cout << "Movie removed from library!" << endl;
            movies.erase(it);
            movieFound = true;
            break;
        }
    }

    if (!movieFound) {
        cout << "Movie not found in library." << endl;
    }
}
    void displayMovies() const 
    {
        cout << "MOVIES IN LIBRARY" << endl;
        cout << "------------------" << endl;
        for (auto m : movies) {
            cout << m.getTitle() << " (" << m.getDirector() << ") [" << m.getFormat() << "]" << endl;
        }
        cout << "------------------" << endl;
    }

    Movie* findMovie(string title) 
    {
        for (auto& m : movies) 
        {
            if (m.getTitle() == title) 
            {
                return &m;
            }
        }
        return nullptr;
    }

    void updateMovie(string title, string director, string format) 
    {
        Movie* m = findMovie(title);
        if (m != nullptr) {
            m->setDirector(director);
            m->setFormat(format);
        }
    }

    void saveLibraryData(string fileName) const 
    {
        ofstream outFile(fileName);

        if (outFile.is_open()) {
            for (auto m : movies) {
                outFile << m.getTitle() << "," << m.getDirector() << "," << m.getFormat() << endl;
            }
            outFile.close();
        }
        else {
            cout << "Error opening file!" << endl;
        }
    }

    void loadLibraryData(string fileName) {
    try {
        ifstream inFile(fileName);
        if (!inFile) {
            throw runtime_error("Error opening file!");
        }

        string title, director, format;
        while (getline(inFile, title, ',') && getline(inFile, director, ',') && getline(inFile, format)) {
            Movie movie(title, director, format);
            addMovie(movie);
        }

        inFile.close();
    }
    catch (const exception& e) {
        cout << e.what() << endl;
    }
}
};

int main() {
    Library library;
    string fileName = "library_data.txt";

    // Load library data from file
    library.loadLibraryData(fileName);
    // Display menu
    int choice = 0;
    while (choice != 6) {
        cout << endl;
        cout << "MENU" << endl;
        cout << "----" << endl;
        cout << "1. Display movies in library" << endl;
        cout << "2. Add a movie" << endl;
        cout << "3. Remove a movie" << endl;
        cout << "4. Update a movie's details" << endl;
        cout << "5. Save library data to file" << endl;
        cout << "6. Quit" << endl;
        cout << endl;

        // Get user choice
        cout << "Enter choice: ";
        cin >> choice;

        // Process user choice
        switch (choice) {
            case 1:
                library.displayMovies();
                break;
            case 2:
                {
                    string title, director, format;
                    cout << "Enter title: ";
                    cin.ignore();
                    getline(cin, title);
                    cout << "Enter director: ";
                    getline(cin, director);
                    cout << "Enter format: ";
                    getline(cin, format);
                    Movie movie(title, director, format);
                    library.addMovie(movie);
                    cout << "Movie added to library!" << endl;
                    break;
                }
            case 3:
                {
                    string title;
                    cout << "Enter title of movie to remove: ";
                    cin.ignore();
                    getline(cin, title);
                    library.removeMovie(title);
                   
                    break;
                }
            case 4:
                {
                    string title, director, format;
                    cout << "Enter title of movie to update: ";
                    cin.ignore();
                    getline(cin, title);
                    Movie* m = library.findMovie(title);
                    if (m != nullptr) {
                        cout << "Enter new director: ";
                        getline(cin, director);
                        cout << "Enter new format: ";
                        getline(cin, format);
                        library.updateMovie(title, director, format);
                        cout << "Movie details updated!" << endl;
                    }
                    else {
                        cout << "Movie not found in library!" << endl;
                    }
                    break;
                }
            case 5:
                library.saveLibraryData(fileName);
                cout << "Library data saved to file!" << endl;
                break;
            case 6:
                cout << "Exiting program." << endl;
                break;
            default:
                cout << "Invalid choice, please try again." << endl;
                break;
        }
    }

    return 0;
}