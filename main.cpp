#include <iostream>
#include <string>
#include <vector>

// We should keep list of programmers CVs
// For each CV we have
//      * name field
//      * birthday year
//      * list of skills
//      * list of previous jobs
//      * we would like to print our CV
class JobRecord
{
public:
    JobRecord(int S_Year, int E_Year, const std::string &JobTitle, const std::string &CompanyName):
        mStartYear{S_Year}
      , mEndYear{E_Year}
      , mJobTitle{JobTitle}
      , mCompanyName{CompanyName}
    {

    }

    bool isValid() const
    {
        return !mJobTitle.empty()
                && ((mStartYear > 1960) && (mEndYear > 1960))
                && !mCompanyName.empty();
    }

    void PrintRecord()
    {
        if(this->isValid())
       {
            std::cout << "Worked as " << mJobTitle << " at " << mCompanyName;
            std::cout << " in (" << mStartYear << " - " << mEndYear << ")" << std::endl;
       }
    }

private:
    int mStartYear;
    int mEndYear;
    std::string mJobTitle;
    std::string mCompanyName;
};

class CV
{
public:
    CV(const std::string &name, int birthYear, const std::string &skills) :
        mName{name}
      , mBirthYear{birthYear}
      , mSkills{skills}
    {

    }

    void addJobRecord (const JobRecord & J_R)
       {
           mPreviousJobs.push_back(J_R);
       }


    bool isValid() const
       {
           bool valid{true};
           valid = !mName.empty()
               && ((mBirthYear > 1970) && (mBirthYear < 1995))
               && !mSkills.empty();
           if (!valid)
               return false;

           for (auto J_R: mPreviousJobs)
           {
               if (!J_R.isValid())
               {
                   valid = false;
                   break;
               }
           }
           return valid;
       }


    void print() const
    {
        if (isValid())
        {
            std::cout << mName << " (" << mBirthYear << ")" << std::endl;
            std::cout << "Skills: " << mSkills << std::endl;
            std::cout << "Previous work record: ";

            for (auto J_R: mPreviousJobs)
            {
                J_R.PrintRecord();
            }
            std::cout << "=====================" << std::endl;
            std::cout << std::endl;
        }
    }

private:
    std::string mName;
    int mBirthYear;
    std::string mSkills;
    std::vector<JobRecord> mPreviousJobs;
};


int main()
{
    CV johnsCV {"John Jonson", 1978,"C++, Java"};

    CV dansCV("Dan Davidson", 1988, "C++, Java");

    johnsCV.addJobRecord(JobRecord(1997,2000,"Junior Developer", "Microsoft" ));
    dansCV.addJobRecord(JobRecord(1999, 2001, "Developer", "IBM"));
    std::vector<CV> cvList {johnsCV, dansCV};

    for (const auto& cv: cvList)
    {
        if (cv.isValid())
        {
            cv.print();
        }
        else
        {
            std::cout << "Error: CV is invalid" << std::endl;
        }
    }

    return 0;
}
