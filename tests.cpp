#include "Account.h"
#include "Transaction.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>

using ::testing::_;
using ::testing::Return;
using ::testing::AtLeast;

class MockAccount: public Account{
public:
      MockAccount(int id, int balance): Account(id, balance){}
      MOCK_METHOD(int, GetBalance, (), (const, override));
      MOCK_METHOD(void, ChangeBalance, (int diff), (override));
      MOCK_METHOD(void, Lock, (), (override));
      MOCK_METHOD(void, Unlock, (), (override));
      MOCK_METHOD(int, id, ());
};

class MockTransaction: public Transaction{
public:
      MockTransaction(): Transaction(){}
      MOCK_METHOD(bool, Make, (Account& from, Account& to, int sum)); 
      MOCK_METHOD(int, fee, (), (const));
      MOCK_METHOD(void, set_fee, (int fee));
};

TEST(Account, TestMethods){
      MockAccount test_account(113'995, 165'500);

      EXPECT_CALL(test_account, id)
	      .Times(1)
	      .WillOnce(Return(113'995));

      test_account.id();

      EXPECT_CALL(test_account, Lock()).Times(2);

      EXPECT_CALL(test_account, Unlock()).Times(2);

      EXPECT_CALL(test_account, GetBalance())
	      .Times(3)
	      .WillOnce(Return(165'500))
	      .WillOnce(Return(135'500))
	      .WillOnce(Return(230'000));

      EXPECT_CALL(test_account, ChangeBalance(_)).Times(AtLeast(2));

      test_account.GetBalance();
      test_account.Lock();
      test_account.ChangeBalance(-30'000);
      test_account.Unlock();
      test_account.GetBalance();
      test_account.Lock();
      test_account.ChangeBalance(94'500);
      test_account.GetBalance();
      test_account.ChangeBalance(0);
      test_account.Unlock();
}

TEST(Transaction, TestMethods){
      MockTransaction test_trans;
}

