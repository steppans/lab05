#include "Account.h"
#include "Transaction.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>

using ::testing::_;

class MockAccount: public Account{
public:
    MockAccount(int id,int balance): Account(id,balance){}
    MOCK_METHOD0(GetBalance, int());
    MOCK_METHOD1(ChangeBalance,void (int diff));
    MOCK_METHOD0(Lock,void());
    MOCK_METHOD0(Unlock,void());
};

class MockTransaction: public Transaction{
public:
    MockTransaction(): Transaction(){}
    MOCK_METHOD(bool, Make, (Account& from,Account& to, int sum));
    MOCK_METHOD(int ,fee,(), (const));
    MOCK_METHOD(void, set_fee,(int fee));
    };

TEST(Transaction,MOCK){
    MockTransaction test;
    Account from(123,10000);
    Account to(345,3000);
    EXPECT_CALL(test,Make)
        .Times(1);
    EXPECT_CALL(test,fee())
        .Times(1);
    EXPECT_CALL(test,set_fee(500))
        .Times(1);

    test.set_fee(500);
    test.fee();
    test.Make(from,to,1000);
}



TEST(Account,MOCK){
    MockAccount test(111,5000);
    EXPECT_CALL(test,GetBalance())
        .Times(2);
    EXPECT_CALL(test,ChangeBalance(_))
        .Times(1);
    EXPECT_CALL(test,Lock())
        .Times(1);
    EXPECT_CALL(test,Unlock())
        .Times(1);

    test.GetBalance();
    test.Lock();
    test.ChangeBalance(1000);
    test.Unlock();
    test.GetBalance();

}

TEST(Account,Work){
    Account test(228337,500000);

    EXPECT_EQ(test.id(),228337);
    EXPECT_EQ(test.GetBalance(), 500000);
    test.Lock();
    test.ChangeBalance(200000);

    EXPECT_EQ(test.GetBalance(), 700000);
    test.Unlock();
    EXPECT_ANY_THROW(test.ChangeBalance(130000));
    EXPECT_EQ(test.GetBalance(), 700000);
    EXPECT_NO_THROW(test.Lock());
    EXPECT_ANY_THROW(test.Lock());
}
TEST(Transaction,Work){
    Account sber(123456, 5000000);
    Account polz(654321, 5000);
    Transaction test_trans;

    test_trans.set_fee(500);
    EXPECT_EQ(test_trans.fee(),500);
    
    EXPECT_TRUE(test_trans.Make(sber,polz, 5000));
    EXPECT_EQ(sber.GetBalance(),4994500);
    EXPECT_EQ(polz.GetBalance(),10000);

    EXPECT_FALSE(test_trans.Make(sber,polz, 5000000));
    EXPECT_EQ(sber.GetBalance(),4994500);
    EXPECT_EQ(polz.GetBalance(),10000);


}

TEST(Transaction,Exeptions){
    Account from(007,10000);
    Account to(001,3000);
    Transaction operation;
    
    EXPECT_ANY_THROW(operation.Make(from, from ,1000));
    EXPECT_ANY_THROW(operation.Make(from,to,-1000));
    EXPECT_ANY_THROW(operation.Make(from,to,50));
    operation.set_fee(2000);
    EXPECT_FALSE(operation.Make(from,to,3000));
}

