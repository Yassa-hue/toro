//
// Created by yassa on 21/11/2022.
//

#ifndef TOROPROJECT_SCOPEMANAGER_H
#define TOROPROJECT_SCOPEMANAGER_H

#include <iostream>
#include <set>
#include <vector>

using namespace std;

class ScopeManager {
private:
    vector <set <string> > scopes;

public:
    ScopeManager();

    bool identifier_is_declared(const string &__ident_name) const;

    void create_inner_scope();

    void pop_out_scope();

    void add_ident_to_curr_scope(const string &__ident_name);
};


#endif //TOROPROJECT_SCOPEMANAGER_H
