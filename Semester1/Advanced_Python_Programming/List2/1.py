def distribution_of_seats(votes, to_be_taken):
    not_included = []
    sum_votes = sum(votes)
    # Nie uwzgledniamy komitetu, jesli jest pod progiem wyborczym
    for i in range(0, len(votes)):
        if (votes[i] / sum_votes) * 100.0 < 5:
            not_included.append(i)
    
    quotients = []
    # Dodajemy kolejne ilorazy i sortujemy je w kolejnosci malejacej
    for i in range(1, to_be_taken + 1):
        for party_index, current_votes in enumerate(votes):
            if party_index not in not_included:
                quotients.append(((current_votes / i), party_index))
    quotients.sort()
    quotients = quotients[::-1]
    
    # Przydzielamy miejsca na podstawie najwiekszych ilorazow
    seats = {}
    for i in range(0, len(votes)):
        seats[i] = 0
    for i in range(0, to_be_taken):
        seats[quotients[i][1]] += 1
    return seats

votes = [720, 300, 480]
to_be_taken = 8
seats = distribution_of_seats(votes, 8)

print("GLOSY UZYSKANE PRZEZ KOMITETY: ")
for i in range(len(votes)):
    print(f"Komitet {i + 1}: ", votes[i])
print(f"MIEJSCA DO OBSADZENIA: {to_be_taken}")
print("PRZYDZIAL MIEJSC: ")
for i in range(len(seats)):
    print(f"Komitet {i + 1}: {seats[i]}")