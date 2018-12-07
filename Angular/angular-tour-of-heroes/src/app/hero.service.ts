import { HttpClient, HttpHeaders } from '@angular/common/http';
import { Injectable } from '@angular/core';
import { Observable, of as observableOf } from 'rxjs';
import { catchError, map, tap } from 'rxjs/operators';

import { Hero } from './hero';
import { MessageService } from './message.service';

const httpOptions = {
  headers: new HttpHeaders({'Content-Type': 'application/json'})
};

@Injectable({
  providedIn: 'root'
})
export class HeroService {
  private heroesUrl = 'api/heroes';

  constructor(
    private http: HttpClient,
    private messageService: MessageService,
  ) { }

  private log(message: string) {
    this.messageService.add(`HeroService: ${message}`);
  }

  private handleError<T> (operation = 'operation', result?: T) {
    return (error: any): Observable<T> => {
      // TODO(youchen): send the error to remote logging infrastructure
      console.error(error);

      // TODO(youchen): better job of transforming error for user consumption
      this.log(`${operation} failed: ${error.message}`);

      return observableOf(result as T);
    };
  }

  getHeroes(): Observable<Hero[]> {
    return this.http.get<Hero[]>(this.heroesUrl)
    .pipe(
      tap(_ => this.log('fetched heroes')),
      catchError(this.handleError('getHeroes', [])),
    );
  }

  getHero(id: number): Observable<Hero> {
    // TODO(youchen): send the message _after_ fetching the hero
    const url = `${this.heroesUrl}/${id}`;
    return this.http.get<Hero>(url)
    .pipe(
      tap(_ => this.log(`fetched hero id=${id}`)),
      catchError(this.handleError<Hero>(`getHero id=${id}`)),
    );
  }

  updateHero(hero: Hero): Observable<any> {
    return this.http.put(this.heroesUrl, hero, httpOptions)
    .pipe(
      tap(_ => this.log(`updated hero id=${hero.id}`)),
      catchError(this.handleError<any>('updateHero')),
    );
  }

  addHero(hero: Hero): Observable<Hero> {
    return this.http.post<Hero>(this.heroesUrl, hero, httpOptions)
    .pipe(
      tap((hero: Hero) => this.log(`added hero w/ id=${hero.id}`)),
      catchError(this.handleError<Hero>('addHero')),
    );
  }

  deleteHero(hero: Hero | number): Observable<Hero> {
    const id = typeof hero === 'number' ? hero : hero.id;
    const url = `${this.heroesUrl}/${id}`;

    return this.http.delete<Hero>(url, httpOptions)
    .pipe(
      tap(_ => this.log(`deleted hero id=${id}`)),
      catchError(this.handleError<Hero>('deleteHero')),
    );
  }

  searchHeroes(term: string): Observable<Hero[]> {
    if (!term.trim()) return observableOf([]);

    return this.http.get<Hero[]>(`${this.heroesUrl}/?name=${term}`)
    .pipe(
      tap(_ => this.log(`found heroes matching "${term}"`)),
      catchError(this.handleError<Hero[]>('searchHeroes', [])),
    );
  }
}
