//
// Created by yassa on 21/11/2022.
//

#include "ScopeManager.h"


ScopeManager::ScopeManager() :scopes() {

}


void ScopeManager::create_inner_scope() {
    // adds a knew scope on the top of scopes stack
    // call it when interring a new inner scope

    scopes.push_back(set<string>());
}


void  ScopeManager::pop_out_scope() {
    // deleting the current scope
    // call it when getting out of the current inner scope

    scopes.pop_back();
}


void ScopeManager::add_ident_to_curr_scope(const string &__ident_name) {
    scopes.back().insert(__ident_name);
}


bool ScopeManager::identifier_is_declared(const string &__ident_name) const {
    // searching for the identifier starting form the inner
    //  scope and going out

    for (int i = scopes.size() -1; i >= 0; --i) {
        if (scopes[i].find(__ident_name) != scopes[i].end())
            return true;
    }

    return false;
}