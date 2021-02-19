public class Test {
    public static void main(String[] args){
        CoinsCollection coins = new ListCC(5, 4, 2);

        try {
            CoinsCollection failed = new ListCC(5, 0, -1);
        } catch (IllegalArgumentException e) {
            System.out.println("1: catched!");
        }

        try {
            coins.addCoin(75);
        } catch (IllegalArgumentException e) {
            System.out.println("2: catched!");
        }

        coins.addCoin(200);
        System.out.println("Total balance is " + coins.balance());

        try {
            CoinsCollection c2 = coins.makeChange(4020);
        } catch (IllegalArgumentException e) {
            System.out.println("3: catched!");
        }

        CoinsCollection nullCoins = coins.makeChange(50000);
        if(nullCoins == null){
            System.out.println("4: verified!");
        }

        CoinsCollection trueCoins = coins.makeChange(50);
        System.out.println(trueCoins.toString());
        System.out.println(coins.toString());
    }
}
