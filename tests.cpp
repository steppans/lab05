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

      EXPECT_CALL(test_account, id())
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

TEST(Account, UsualWork){
      Account test(513'680, 500'000);

      EXPECT_EQ(test.id(), 513'680);
      EXPECT_NE(test.id(), 80'986);
      EXPECT_EQ(test.GetBalance(), 500'000);

      test.Lock();
      test.ChangeBalance(200'000);

      EXPECT_EQ(test.GetBalance(), 700'000);

      test.Unlock();

      EXPECT_ANY_THROW(test.ChangeBalance(130'000));
      EXPECT_EQ(test.GetBalance(), 700'000);
      
      EXPECT_NO_THROW(test.Lock());
      EXPECT_ANY_THROW(test.Lock());
}

TEST(Transaction, TestMethods){
      Account user_from(231, 67'000);
      Account user_to(456, 35'000);
      MockTransaction test_transaction;
      
      EXPECT_CALL(test_transaction, fee())
	      .Times(3)
              .WillOnce(Return(1))
	      .WillRepeatedly(Return(500));

      EXPECT_CALL(test_transaction, set_fee(_))
	      .Times(1);

      EXPECT_CALL(test_transaction, Make)
	      .Times(AtLeast(1));

      test_transaction.fee();
      test_transaction.set_fee(500);
      test_transaction.fee();

      // First transaction
      test_transaction.Make(user_from, user_to, 30'000);

      // Second transaction
      test_transaction.Make(user_from, user_to, 40'000);

      test_transaction.fee();
}

TEST(Transaction, UsualWork){
      Account bank(111'996, 1'000'000);
      Account user(55'984, 13'000);
      Transaction test_trans; 

      EXPECT_EQ(test_trans.fee(), 1);     
      test_trans.set_fee(1000);
      EXPECT_EQ(test_trans.fee(), 1000);

      EXPECT_TRUE(test_trans.Make(bank, user, 10'000));
      EXPECT_EQ(bank.GetBalance(), 989'000);
      EXPECT_EQ(user.GetBalance(), 23'000);
}

TEST(Transaction, Exceptions){
      Account user_from(876, 9'000);
      Account user_to(478, 1'000);
      Transaction test_trans;

      EXPECT_THROW(test_trans.Make(user_from, user_from, 7'000), std::logic_error);
      EXPECT_THROW(test_trans.Make(user_from, user_to, -850), std::invalid_argument);
      EXPECT_THROW(test_trans.Make(user_from, user_to, 50), std::logic_error);

      test_trans.set_fee(2'000);
      EXPECT_EQ(test_trans.fee(), 2'000);
      EXPECT_FALSE(test_trans.Make(user_from, user_to, 2'500));
      EXPECT_EQ(user_from.GetBalance(), 9'000);
      EXPECT_EQ(user_to.GetBalance(), 1'000);      

      EXPECT_FALSE(test_trans.Make(user_from, user_to, 8'000));
      EXPECT_EQ(user_from.GetBalance(), 9'000);
      EXPECT_EQ(user_to.GetBalance(), 1'000);      
}
