package is1;

public class Paper implements Move {

    public Move vs(Move other) {
        return other.againstPaper(this);
    }

    public Move againstRock(Move other) {
        return this;
    }

    public Move againstPaper(Move other) { return this; }

    public Move againstScissors(Move other) {
        return other;
    }
}
