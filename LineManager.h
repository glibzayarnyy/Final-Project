// Name: Glib Zayarnyy
// Seneca Student ID: 102086170
// Seneca email: gzayarnyy@myseneca.ca
// Date of completion: December 2nd, 2018
//
// I confirm that I am the only author of this file
// and the content was created entirely by me.

#ifndef LINEMANAGER_H
#define LINEMANAGER_H
#include <vector>
#include <deque>
#include <iostream>
#include "Task.h"
#include "CustomerOrder.h"


class LineManager {
    std::vector<Task*> AssemblyLine;
    std::deque<CustomerOrder> ToBeFilled;
    std::deque<CustomerOrder> Completed;
    unsigned int m_cntCustomerOrder;
    size_t m_firstTask;
    size_t m_lastTask;

    public:
        LineManager(const std::string&, std::vector<Task*>&, std::vector<CustomerOrder>&);
        bool run(std::ostream&);
        void displayCompleted(std::ostream&) const;
        void validateTasks() const;
};

#endif // LINEMANAGER_H