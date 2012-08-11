package org.thagey.war;

public class Card implements Comparable<Card> {
	public enum Suit { HEARTS, SPADES, CLUBS, DIAMONDS };
	public enum Rank { TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING, ACE, JOKER };

	private final Suit m_suit;
	private final Rank m_rank;
	
	public Card(Suit s, Rank r) {
		if (r == null) {
			throw new IllegalArgumentException("invalid rank");
		}
		m_suit = s;
		m_rank = r;
	}
	
	public int compareTo(Card c) {
		if (c == null) { return Integer.MAX_VALUE; }
		return m_rank.ordinal() - c.m_rank.ordinal();
	}
	
	@Override
	public String toString() {
		StringBuilder sb = new StringBuilder(m_rank.name());
		if (m_suit != null) {
			sb.append(" of ");
			sb.append(m_suit.name());
		}
		return sb.toString();
	}
}
