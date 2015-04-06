#include <iostream>
#include <cstdio>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <cmath>

using namespace std;

class No
{
    private:
        int x, y;

    public:
        No(int x, int y) {
            this->x = x;
            this->y = y;
        }

        int getX() {
            return x;
        }

        int getY() {
            return y;
        }
};

class NoLista
{
    private:
        No *no;
        double peso;
        NoLista *next;

    public:
        NoLista(No *no, double peso) {
            this->no = no;
            this->peso = peso;
            next = NULL;
        }

        No* getNo() {
            return no;
        }

        double getPeso() {
            return peso;
        }

        NoLista* getNext() {
            return next;
        }

        void setNext(NoLista *next) {
            this->next = next;
        }

        void setPeso(double peso) {
            this->peso = peso;
        }
};

class NoIndice
{
    private:
        No *no;
        NoIndice *next;
        NoLista *lista;

    public:
        NoIndice(No *no) {
            this->no = no;
            next = next = NULL;
        }

        No* getNo() {
            return no;
        }

        NoIndice* getNext() {
            return next;
        }

        NoLista* getLista() {
            return lista;
        }

        void setNext(NoIndice *next) {
            this->next = next;
        }

        void setLista(NoLista *lista) {
            this->lista = lista;
        }
};

class Grafo
{
    private:
        NoIndice *inicioGrafo;
        NoIndice *inicioAGM;
        int numeroNos;

        double calcularMedia();

        void construirListaAdjacencia(double);

        void calcularNumeroNos();

        bool verificarDisponibilidade(bool*,int,int);

        void adicionarArestaAGM(No*,No*,double);

        int getIndice(No*);

        void alterarPeso(No*,No*,double);

        void inserirAresta(NoIndice*,No*,No*,double);

        void removerAresta(NoIndice*,No*,No*);

        bool verificarVetor(No*,No**,int);

    public:
        Grafo() {
            inicioGrafo = new NoIndice(NULL);
            inicioAGM = new NoIndice(NULL);
            numeroNos = 0;
        }

        NoIndice* getInicioGrafo() {
            return inicioGrafo;
        }

        NoIndice* getInicioAGM() {
            return inicioAGM;
        }

        int getNumeroNos() {
            return numeroNos;
        }

        void lerArquivo();

        void imprimirGrafo(NoIndice*,bool,string);

        void algoritmoPrim();

        void alterarPesoAresta(No*,No*,double);

        void inserirArestaGrafo(NoIndice*,No*,No*,double);

        void removerArestaGrafo(No*,No*);

        void recalcularAGM(No*,No*);

        double verificarAresta(NoIndice*,No*,No*);
};

bool Grafo::verificarVetor(No *no, No **vetor, int tam)
{
    int i;
    for(i=0;i<tam;i++)
    {
        if(no->getX()==vetor[i]->getX() && no->getY()==vetor[i]->getY()) return true;
    }
    return false;
}

double Grafo::verificarAresta(NoIndice *inicio, No *origem, No *destino)
{
    NoIndice *p;
    NoLista *q;
    p = inicio->getNext();
    if(p==NULL) return -1;
    while(p->getNext()!=NULL && (p->getNo()->getX()!=origem->getX() || p->getNo()->getY()!=origem->getY())) p = p->getNext();
    if(p->getNext()==NULL && (p->getNo()->getX()!=origem->getX() || p->getNo()->getY()!=origem->getY())) return -1;
    q = p->getLista();
    while(q!=NULL)
    {
        if(q->getNo()->getX()==destino->getX() && q->getNo()->getY()==destino->getY()) return q->getPeso();
        q = q->getNext();
    }
    return -1;
}

void Grafo::recalcularAGM(No *origem, No *destino)
{
    NoIndice *p;
    NoLista *q;
    No *vet[numeroNos-1],*n1,*n2;
    int cont=1,i;
    double menorPeso;
    bool acabou,menorInicializado=false;
    p = inicioAGM->getNext();
    if(p==NULL) return;
    while(p->getNext()!=NULL && (p->getNo()->getX()!=origem->getX() || p->getNo()->getY()!=origem->getY())) p = p->getNext();
    if(p->getNext()==NULL && (p->getNo()->getX()!=origem->getX() || p->getNo()->getY()!=origem->getY())) return;
    vet[0] = p->getNo();
    while(cont<numeroNos)
    {
        p = inicioAGM->getNext();
        acabou = true;
        while(p!=NULL)
        {
            if(verificarVetor(p->getNo(),vet,cont))
            {
                q = p->getLista();
                while(q!=NULL)
                {
                    if(!verificarVetor(q->getNo(),vet,cont))
                    {
                        acabou = false;
                        cont++;
                        vet[cont-1] = q->getNo();
                    }
                    q = q->getNext();
                }
            }
            p = p->getNext();
        }
        if(acabou) break;
    }
    for(i=0;i<cont;i++)
    {
        p = inicioAGM->getNext();
        while(p!=NULL)
        {
            if(!verificarVetor(p->getNo(),vet,cont))
            {
                if(verificarAresta(inicioGrafo,p->getNo(),vet[i])!=-1)
                {
                    if(!menorInicializado)
                    {
                        menorPeso = verificarAresta(inicioGrafo,p->getNo(),vet[i]);
                        n1 = p->getNo();
                        n2 = vet[i];
                        menorInicializado = true;
                    }
                    else if(menorPeso > verificarAresta(inicioGrafo,p->getNo(),vet[i]))
                    {
                        menorPeso = verificarAresta(inicioGrafo,p->getNo(),vet[i]);
                        n1 = p->getNo();
                        n2 = vet[i];
                    }
                }
            }
            p = p->getNext();
        }
    }
    inserirArestaGrafo(inicioAGM,n1,n2,menorPeso);
}

void Grafo::removerAresta(NoIndice *inicio, No *origem, No *destino)
{
    NoIndice *p;
    NoLista *q,*r;
    p = inicio->getNext();
    if(p==NULL) return;
    while(p->getNext()!=NULL && (p->getNo()->getX()!=origem->getX() || p->getNo()->getY()!=origem->getY())) p = p->getNext();
    if(p->getNext()==NULL && (p->getNo()->getX()!=origem->getX() || p->getNo()->getY()!=origem->getY())) return;
    q = p->getLista();
    if(q==NULL) return;
    if(q->getNo()->getX()==destino->getX() && q->getNo()->getY()==destino->getY())
    {
        p->setLista(q->getNext());
        free(q);
        return;
    }
    while(q->getNext()!=NULL)
    {
        if(q->getNext()->getNo()->getX()==destino->getX() && q->getNext()->getNo()->getY()==destino->getY())
        {
            r = q->getNext();
            q->setNext(r->getNext());
            free(r);
            return;
        }
        q = q->getNext();
    }
}

void Grafo::removerArestaGrafo(No *origem, No *destino)
{
    removerAresta(inicioGrafo,origem,destino);
    removerAresta(inicioGrafo,destino,origem);
    removerAresta(inicioAGM,origem,destino);
    removerAresta(inicioAGM,destino,origem);
}

void Grafo::inserirAresta(NoIndice *inicio, No *origem, No *destino, double peso)
{
    NoIndice *p;
    NoLista *q;
    p = inicio->getNext();
    if(p==NULL) return;
    while(p->getNext()!=NULL && (p->getNo()->getX()!=origem->getX() || p->getNo()->getY()!=origem->getY())) p = p->getNext();
    if(p->getNext()==NULL && (p->getNo()->getX()!=origem->getX() || p->getNo()->getY()!=origem->getY())) return;
    q = p->getLista();
    if(q==NULL)
    {
        p->setLista(new NoLista(destino,peso));
        return;
    }
    while(q->getNext()!=NULL)
    {
        if(q->getNo()->getX()==destino->getX() && q->getNo()->getY()==destino->getY()) return;
        q = q->getNext();
    }
    q->setNext(new NoLista(destino,peso));
}

void Grafo::inserirArestaGrafo(NoIndice *inicio, No *origem, No *destino, double peso)
{
    inserirAresta(inicio,origem,destino,peso);
    inserirAresta(inicio,destino,origem,peso);
}

void Grafo::calcularNumeroNos()
{
    NoIndice *p;
    p = inicioGrafo->getNext();
    while(p!=NULL)
    {
        numeroNos++;
        p = p->getNext();
    }
}

double Grafo::calcularMedia()
{
    int soma=0,cont=0;
    NoIndice *p,*q;
    p = inicioGrafo->getNext();
    while(p!=NULL)
    {
        q = p->getNext();
        while(q!=NULL)
        {
            soma += sqrt(pow(p->getNo()->getX() - q->getNo()->getX(),2) + pow(p->getNo()->getY() - q->getNo()->getY(),2));
            cont++;
            q = q->getNext();
        }
        p = p->getNext();
    }
    if(cont==0) return 0;
    return (double)soma/cont;
}

void Grafo::construirListaAdjacencia(double limite)
{
    double peso;
    NoIndice *p,*q;
    NoLista *r;
    p = inicioGrafo->getNext();
    while(p!=NULL)
    {
        q = inicioGrafo->getNext();
        while(q!=NULL)
        {
            if(p->getNo()->getX()!=q->getNo()->getX() || p->getNo()->getY()!=q->getNo()->getY())
            {
                peso = sqrt(pow(p->getNo()->getX() - q->getNo()->getX(),2) + pow(p->getNo()->getY() - q->getNo()->getY(),2));
                if(peso<=limite)
                {
                    if(p->getLista()==NULL)
                    {
                        p->setLista(new NoLista(q->getNo(),peso));
                        r = p->getLista();
                    }
                    else
                    {
                        r->setNext(new NoLista(q->getNo(),peso));
                        r = r->getNext();
                    }
                }
            }
            q = q->getNext();
        }
        p = p->getNext();
    }
    calcularNumeroNos();
}

void Grafo::lerArquivo()
{
    int i,tam,porcentagem,x,y;
    double limite;
    NoIndice *p;
    FILE *arquivo;
    arquivo = fopen("arqEntrada.txt","r");
    fscanf(arquivo,"%d",&tam);
    for(i=0;i<tam;i++)
    {
        fscanf(arquivo,"%d %d",&x,&y);
        if(inicioGrafo->getNext()==NULL)
        {
            inicioGrafo->setNext(new NoIndice(new No(x,y)));
            p = inicioGrafo->getNext();
        }
        else
        {
            p->setNext(new NoIndice(new No(x,y)));
            p = p->getNext();
        }
    }
    fscanf(arquivo,"%d",&porcentagem);
    fclose(arquivo);
    limite = calcularMedia() * (porcentagem/100 + 1);
    construirListaAdjacencia(limite);
}

void Grafo::imprimirGrafo(NoIndice *inicio, bool append, string titulo)
{
    NoIndice *p;
    NoLista *q;
    fstream arquivo;
    if(append) arquivo.open("arqSaida.txt",fstream::out | fstream::app);
    else arquivo.open("arqSaida.txt",fstream::out | fstream::trunc);
    arquivo.setf(ios::fixed);
    arquivo.precision(2);
    if(append) arquivo << "\n";
    arquivo << titulo << ":\n\n";
    p = inicio->getNext();
    while(p!=NULL)
    {
        arquivo << "(" << p->getNo()->getX() << "," << p->getNo()->getY() << ") ->";
        q = p->getLista();
        while(q!=NULL)
        {
            arquivo << " (" << q->getNo()->getX() << "," << q->getNo()->getY() << ")" << q->getPeso() << ";";
            q = q->getNext();
        }
        arquivo << "\n";
        p = p->getNext();
    }
    arquivo.close();
}

bool Grafo::verificarDisponibilidade(bool* vet, int x, int y)
{
    NoIndice *p;
    int cont=0;
    p = inicioGrafo->getNext();
    if(p==NULL) return false;
    while(p->getNext()!=NULL && (p->getNo()->getX()!=x || p->getNo()->getY()!=y))
    {
        cont++;
        p = p->getNext();
    }
    if(p->getNext()==NULL && (p->getNo()->getX()!=x || p->getNo()->getY()!=y)) return false;
    if(vet[cont]) return false;
    return true;
}

void Grafo::adicionarArestaAGM(No *origem, No *destino, double peso)
{
    NoIndice *r;
    NoLista *s;
    r = inicioAGM->getNext();
    while(r->getNext()!=NULL && (r->getNo()->getX()!=origem->getX() || r->getNo()->getY()!=origem->getY())) r = r->getNext();
    if(r->getNext()==NULL && (r->getNo()->getX()!=origem->getX() || r->getNo()->getY()!=origem->getY()))
    {
        r->setNext(new NoIndice(origem));
        r = r->getNext();
    }
    s = r->getLista();
    if(s==NULL) r->setLista(new NoLista(destino,peso));
    else
    {
        while(s->getNext()!=NULL) s = s->getNext();
        s->setNext(new NoLista(destino,peso));
    }
}

int Grafo::getIndice(No *no)
{
    int cont=0;
    NoIndice *p;
    p = inicioGrafo->getNext();
    while(p->getNo()->getX()!= no->getX() || p->getNo()->getY()!= no->getY())
    {
        cont++;
        p = p->getNext();
    }
    return cont;
}

void Grafo::algoritmoPrim()
{
    NoIndice *p;
    NoLista *q;
    bool vet[numeroNos],menorInicializado;
    int i,cont;
    double menorPeso;
    No *menorNoP,*menorNoQ;
    vet[0] = true;
    for(i=1;i<numeroNos;i++) vet[i] = false;
    inicioAGM->setNext(new NoIndice(inicioGrafo->getNext()->getNo()));
    for(i=0;i<numeroNos-1;i++)
    {
        p = inicioGrafo->getNext();
        cont = 0;
        menorInicializado = false;
        while(p!=NULL)
        {
            if(vet[cont])
            {
                q = p->getLista();
                while(q!=NULL)
                {
                    if(verificarDisponibilidade(vet,q->getNo()->getX(),q->getNo()->getY()))
                    {
                        if(menorInicializado)
                        {
                            if(q->getPeso() < menorPeso)
                            {
                                menorPeso = q->getPeso();
                                menorNoP = p->getNo();
                                menorNoQ = q->getNo();
                            }
                        }
                        else
                        {
                            menorPeso = q->getPeso();
                            menorNoP = p->getNo();
                            menorNoQ = q->getNo();
                            menorInicializado = true;
                        }
                    }
                    q = q->getNext();
                }
            }
            cont++;
            p = p->getNext();
        }
        vet[getIndice(menorNoQ)] = true;
        adicionarArestaAGM(menorNoP,menorNoQ,menorPeso);
        adicionarArestaAGM(menorNoQ,menorNoP,menorPeso);
    }
}

void Grafo::alterarPeso(No *origem, No *destino, double peso)
{
    NoIndice *p;
    NoLista *q;
    p = inicioGrafo->getNext();
    if(p==NULL) return;
    while(p->getNext()!=NULL && (p->getNo()->getX()!=origem->getX() || p->getNo()->getY()!=origem->getY())) p = p->getNext();
    if(p->getNext()==NULL && (p->getNo()->getX()!=origem->getX() || p->getNo()->getY()!=origem->getY())) return;
    q = p->getLista();
    if(q==NULL) return;
    while(q->getNext()!=NULL && (q->getNo()->getX()!=destino->getX() || q->getNo()->getY()!=destino->getY())) q = q->getNext();
    if(q->getNext()==NULL && (q->getNo()->getX()!=destino->getX() || q->getNo()->getY()!=destino->getY())) return;
    q->setPeso(peso);
}

void Grafo::alterarPesoAresta(No *origem, No *destino, double peso)
{
    alterarPeso(origem,destino,peso);
    alterarPeso(destino,origem,peso);
    if(verificarAresta(inicioAGM,origem,destino)!=-1)
    {
        removerAresta(inicioAGM,origem,destino);
        removerAresta(inicioAGM,destino,origem);
    }
}

int main()
{
    int n,x1,x2,y1,y2;
    double peso;
    stringstream a,b,c,d;
    Grafo g;
    g.lerArquivo();
    g.imprimirGrafo(g.getInicioGrafo(),false,"Grafo");
    g.algoritmoPrim();
    g.imprimirGrafo(g.getInicioAGM(),true,"AGM");
    cout << "O que deseja fazer?\n\n(1) Alterar o peso de uma aresta\n(2) Inserir uma aresta\n(3) Remover uma aresta\n(4) Sair do programa\n\n";
    while(cin >> n)
    {
        if(n==1 || n==2 || n==3)
        {
            cout << "\nDigite as coordenadas do primeiro nó da aresta: ";
            cin >> x1 >> y1;
            cout << "\nDigite as coordenadas do segundo nó da aresta: ";
            cin >> x2 >> y2;
            a.str("");
            b.str("");
            c.str("");
            d.str("");
            a << x1;
            b << y1;
            c << x2;
            d << y2;
        }
        switch(n)
        {
            case 1:
                if(g.verificarAresta(g.getInicioGrafo(),new No(x1,y1),new No(x2,y2))==-1)
                {
                    cout << "\nEsta aresta não existe no grafo\n";
                    break;
                }
                cout << "\nDigite o novo peso da aresta: ";
                cin >> peso;
                g.alterarPesoAresta(new No(x1,y1),new No(x2,y2),peso);
                g.recalcularAGM(new No(x1,y1),new No(x2,y2));
                g.imprimirGrafo(g.getInicioAGM(),true,"Modificando a aresta entre os nós ("+a.str()+string(",")+b.str()+string(") e (")+c.str()+string(",")+d.str()+string(")"));
                break;
            case 2:
                if(g.verificarAresta(g.getInicioGrafo(),new No(x1,y1),new No(x2,y2))!=-1)
                {
                    cout << "\nEsta aresta já existe no grafo\n";
                    break;
                }
                cout << "\nDigite o peso da aresta: ";
                cin >> peso;
                g.inserirArestaGrafo(g.getInicioGrafo(),new No(x1,y1),new No(x2,y2),peso);
                g.imprimirGrafo(g.getInicioAGM(),true,"Inserindo a aresta entre os nós ("+a.str()+string(",")+b.str()+string(") e (")+c.str()+string(",")+d.str()+string(")"));
                break;
            case 3:
                if(g.verificarAresta(g.getInicioGrafo(),new No(x1,y1),new No(x2,y2))==-1)
                {
                    cout << "\nEsta aresta não existe no grafo\n";
                    break;
                }
                g.removerArestaGrafo(new No(x1,y1),new No(x2,y2));
                g.recalcularAGM(new No(x1,y1),new No(x2,y2));
                g.imprimirGrafo(g.getInicioAGM(),true,"Removendo a aresta entre os nós ("+a.str()+string(",")+b.str()+string(") e (")+c.str()+string(",")+d.str()+string(")"));
                break;
            case 4:
                return 0;
            default:
                cout << "\nOpção inválida\n";
        }
        cout << "\nO que deseja fazer?\n\n(1) Alterar o peso de uma aresta\n(2) Inserir uma aresta\n(3) Remover uma aresta\n(4) Sair do programa\n\n";
    }
    return 0;
}
