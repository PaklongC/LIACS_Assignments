class stapel{
	public:
		stapel(); //constructor
		~stapel(); //destructor
		void push(stapel* & in, int m, int n); // functie die waarde in stack pusht
		void pop(stapel* &in); // functie die waarde uit stack haalt teruggeeeft end delete
		int coordinaatRij(stapel* &in); //returned memb variabel infoRij
		int coordinaatKolom(stapel* &in); // returned memb variabel infoKolom

	private:
        int infoRij, infoKolom; //coordinaten van opgeslagen zetten
        int* andere; //pointer naar andere waarde
        stapel* volgende; //pointer naar bovenste item
};
