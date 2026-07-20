package is1;

public class Scissors implements Move {

    public Move vs(Move other) {
        return other.againstScissors(this);
    }

    public Move againstRock(Move other) {
        return other;
    }

    public Move againstPaper(Move other) {
        return this;
    }

    public Move againstScissors(Move other) { return this; }

}
