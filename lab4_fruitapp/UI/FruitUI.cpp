//
// Created by Latitude on 24.04.2023.
//

#include "FruitUI.h"
#include "../Controller/FruitController.h"
#include <iostream>
#include <string>


namespace ui {
    FruitUI::FruitUI(controller::FruitController& ctrl) : ctrl(ctrl) {
        //add 10 fruits
        ctrl.add("Banana","Uganda","2022/01/23",3,2);
        ctrl.add("Banana","Bolivia","2022/01/23",5,4);
        ctrl.add("Apple","Germany","2023/01/25",1,1);
        ctrl.add("Apple","Romania","2024/07/27",1,2);
        ctrl.add("Kiwi","Marocco","2023/05/23",3,12);
        ctrl.add("Orange","Mexico","2023/09/03",5,20);
        ctrl.add("Strawberry","Albania","2023/07/19",3,1);
        ctrl.add("Raspberry","Albania","2023/02/23",2,17);
        ctrl.add("Raspberry","Italy","2023/04/23",2,15);
        ctrl.add("Dragonfruit","India","2024/01/01",20,1);

    }

    void FruitUI::menu(){
        cout <<  "  _____           _ _                    \n"
                 " |  ___| __ _   _(_) |_ __ _ _ __  _ __  \n"
                 " | |_ | '__| | | | | __/ _` | '_ \\| '_ \\ \n"
                 " |  _|| |  | |_| | | || (_| | |_) | |_) |\n"
                 " |_|  |_|   \\__,_|_|\\__\\__,_| .__/| .__/ \n"
                 "                            |_|   |_|  ";

        int input = 1;
        while(input != 0){

            cout <<"\n\n\nChoose an option:\n"
                   "1.Add fruit\n"
                   "2.Delete fruit\n"
                   "3.Search fruit\n"
                   "4.Show shortage\n"
                   "5.Show fruits sorted after expiration date\n"
                   "0.Exit\n";

            cin >> input;

            switch (input) {
                case 1:
                    option_add();
                    break;
                case 2:
                    option_delete();
                    break;
                case 3:
                    option_search();
                    break;
                case 4:
                    option_show_shortage();
                    break;
                case 5:
                    option_show_sorted_expirationdate();
                    break;
            }
        }
    }

    void FruitUI::option_add() {

        string name;
        string origin;
        string expirationdate;
        string input;
        int quantity;
        int price;

        cout << "\nFruit name: ";
        cin >> name;
        cout << "\nFruit origin: ";
        cin >> origin;
        cout << "\nExpirationdate, in format YYYY/MM/DD: ";
        cin >> expirationdate;

        while(true){
            cout << "\nQuantity (only int is allowed): ";
            cin >> input;
            try {
                quantity = stoi(input);
            } catch (const exception& e){
                cout << "Error: Input is not int, try again";
                continue;
            }
            break;
        }

        while(true){
            cout << "\nPrice (only int is allowed): ";
            cin >> input;
            try {
                price = stoi(input);
            } catch (const exception& e){
                cout << "Error: Input is not int, try again";
                continue;
            }
            break;
        }

        ctrl.add(name,origin,expirationdate,price,quantity);
    }
    void FruitUI::option_delete() {

        string name;
        string origin;

        cout << "\nFruit name: ";
        cin >> name;
        cout << "\nFruit origin: ";
        cin >> origin;

        ctrl.delete_fruit(name,origin);
    }
    void FruitUI::option_search() {

        string substring;
        cout << "\nSearch: ";
        cin >> substring;
        shared_ptr<vector<shared_ptr<domain::Fruit>>> fruitlist = ctrl.find_with_substring(substring);
        print_fruits(fruitlist);
    }

    void FruitUI::option_show_shortage() {
        int max_quantity;
        cout << "\nmaximum quantity";
        cin >> max_quantity;

        shared_ptr<vector<shared_ptr<domain::Fruit>>> fruitlist = ctrl.filter_shortage(max_quantity);
        print_fruits(fruitlist);
    }

    void FruitUI::option_show_sorted_expirationdate() {
        shared_ptr<vector<shared_ptr<domain::Fruit>>> fruitlist = ctrl.sorted_expiration_date();
        print_fruits(fruitlist);
    }

    void FruitUI::print_fruits(shared_ptr<vector<shared_ptr<domain::Fruit>>> fruitlist){

        cout << "\n\nname: origin: expiration date: quantity: price\n";
        for(int i = 0;i < (*fruitlist).size(); i++){
            cout << (*fruitlist)[i]->get_name() << ": " << (*fruitlist)[i]->get_origin() << ": "<<(*fruitlist)[i]->get_expirationdate() << ": " << (*fruitlist)[i]->get_quantity() << ": "<<(*fruitlist)[i]->get_price()<<"\n";
        }
    }
}


